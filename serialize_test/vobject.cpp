#include <QDebug>
#include <QMetaEnum>
#include <QMetaObject>
#include <QMetaProperty>

#include "vmetadump.h"
#include "vobject.h"

void VObject::load(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int count = mobj->propertyCount();
	for (int i = 0; i < count; i++)
	{
		QMetaProperty mpro     = mobj->property(i);
		const char*   name     = mpro.name();
		QVariant      from     = rep[name];
		int           userType = mpro.userType();

		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			QString   key   = from.toString();
			QVariant  to    = menum.keyToValue(qPrintable(key));
			this->setProperty(name, to);
		} else
		if (QMetaType::hasRegisteredConverterFunction(QVariant::String, userType))
		{
			QVariant to(userType, NULL);
			void* fromData     = from.data();
			int   fromUserType = from.userType(); // QVariant::String
			void* toData       = to.data();
			int   toUserType   = to.userType();
			bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
			if (!res)
			{
				printf("VObject::save QMetaType::convert return false name=%s\n", name); // gilgil temp 2015.01.07
				VMetaDump::dump(&from); // gilgil temp 2015.01.07
			}
			this->setProperty(name, to);
		} else
		if (userType == qMetaTypeId<VObject*>())
		{
			VObject* childObj = this->property(name).value<VObject*>();
			VRep     childRep = rep[name].toMap();
			childObj->load(childRep);
		} else
		if (userType == qMetaTypeId<VObjectList*>())
		{
			VObjectList* childObjList = this->property(name).value<VObjectList*>();
			VRep childRepList = rep[name].toMap();
			printf("%d\n", childRepList.count()); // gilgil temp 2015.01.07
			for (VRep::iterator it = childRepList.begin(); it != childRepList.end(); it++)
			{
				VRep childRep = it->toMap();
				// ----- gilgil temp 2015.01.08 -----
				/*
				QString className = childRep["_class"].toString();
				int id = QMetaType::type(qPrintable(className)); // gilgil temp 2015.01.07
				//int id = QMetaType::type("VObject");
				if (id == QMetaType::UnknownType) {
					printf("can not resolve type for class %s\n", qPrintable(className));
					continue;
				}
				void* obj = QMetaType::create(id);
				VObject* vobj = (VObject*)obj;
				*/
				// ----------------------------------
				VObject* vobj = childObjList->createObject();
				//VObject* vobj = qvariant_cast<VObject*>(QMetaType::create(id));
				vobj->load(childRep);
				childObjList->push_back(vobj);
			}
			//QVariant to = QVariant::fromValue<VObjectList>(childObjList);
			//this->setProperty(name, to);
		} else
		{
			this->setProperty(name, from);
		}
	}
	// ----- gilgil temp 2015.01.08 -----
	/*
	QString className = rep["_class"].toString();
	if (className != this->metaObject()->className())
	{
		printf("different class name (%s) and (%s)", qPrintable(className), this->metaObject()->className());
	}
	*/
	// ----------------------------------
}

void VObject::save(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int count = mobj->propertyCount();
	for (int i = 0; i < count; i++)
	{
		QMetaProperty mpro     = mobj->property(i);
		const char*   name     = mpro.name();
		QVariant      from     = this->property(name);
		int           userType = mpro.userType();

		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			int       index = from.toInt();
			QString   to    = menum.key(index);
			rep[name] = to;
		} else
		if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
		{
			QVariant to(QVariant::String, NULL);
			void* fromData     = from.data();
			int   fromUserType = from.userType();
			void* toData       = to.data();
			int   toUserType   = to.userType(); // QVariant::String
			bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
			if (!res)
			{
				printf("VObject::load QMetaType::convert return false name=%s\n", name); // gilgil temp 2015.01.07
				VMetaDump::dump(&from); // gilgil temp 2015.01.07
				VMetaDump::dump(&to); // gilgil temp 2015.01.07
			}
			rep[name] = to;
		} else
		if (userType == qMetaTypeId<VObject*>())
		{
			VObject* childObj = this->property(name).value<VObject*>();
			VRep     childRep;
			childObj->save(childRep);
			rep[name] = childRep;
		} else
		if (userType == qMetaTypeId<VObjectList*>())
		{
			VObjectList* childObjList = this->property(name).value<VObjectList*>();
			VRep childRepList;
			int i = 0;
			foreach (VObject* childObj, *childObjList)
			{
				VRep childRep;
				childObj->save(childRep);
				childRepList[QString::number(i)] = childRep;
				i++;
			}
			rep[name] = childRepList;
		} else
		{
			if (!(QString(name) == "objectName" && from == ""))
				rep[name] = from;
		}
	}
	// rep["_class"] = this->metaObject()->className(); // gilgil temp 2015.01.08
}

bool VObject::loadFromFile(QString fileName)
{
	VRep rep;
	if (!rep.loadFromFile(fileName))
		return false;
	this->load(rep);
	return true;
}

bool VObject::saveToFile(QString fileName)
{
	VRep rep;
	this->save(rep);
	return rep.saveToFile(fileName);
}

#ifdef QT_GUI_LIB
VWidget* VObject::createWidget()
{
	VWidgetObject* wobj = new VWidgetObject;
	//QObject::connect(wobj, SIGNAL(itemChanged(QTreeWidgetItem*,int)), this, SLOT(itemChanged(QTreeWidgetItem*,int)));
	QObject::connect(wobj, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(itemChanged(QTreeWidgetItem*,int)));

	wobj->setColumnCount(2);

	const QMetaObject *mobj = this->metaObject();
	int count = this->metaObject()->propertyCount();
	for (int i = 0; i < count; i++)
	{
		QMetaProperty mpro     = mobj->property(i);
		const char*   name     = mpro.name();
		QVariant      from     = this->property(name);
		int           userType = mpro.userType();

		if (mpro.isEnumType())
		{
		} else
		if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
		{
		} else
		if (userType == qMetaTypeId<VObject*>())
		{
		} else
		if (userType == qMetaTypeId<VObjectList*>())
		{
		} else
		{
			VWidgetItem* witem = new VWidgetItem(&from, wobj);
			witem->setText(0, name);
			witem->setText(1, from.toString());
			witem->setFlags(witem->flags() | Qt::ItemIsEditable);
		}
	}
	return wobj;
}

void VObject::itemChanged(QTreeWidgetItem *item, int column)
{
	QString s = item->text(0);
	int i = s.toInt();
	s = QString::number(i);
	item->setText(0, s);
}

#endif // QT_GUI_LIB
