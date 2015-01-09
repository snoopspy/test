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
		const char*   propName = mpro.name();
		QVariant      from     = rep[propName];
		int           userType = mpro.userType();

		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			QString   key   = from.toString();
			QVariant  to    = menum.keyToValue(qPrintable(key));
			this->setProperty(propName, to);
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
				printf("VObject::save QMetaType::convert return false name=%s\n", propName); // gilgil temp 2015.01.07
				VMetaDump::dump(&from); // gilgil temp 2015.01.07
			}
			this->setProperty(propName, to);
		} else
		if (userType == qMetaTypeId<VObject*>())
		{
			VObject* childObj = this->property(propName).value<VObject*>();
			VRep     childRep = rep[propName].toMap();
			childObj->load(childRep);
		} else
		if (userType == qMetaTypeId<VObjectList*>())
		{
			VObjectList* childObjList = this->property(propName).value<VObjectList*>();
			VRep childRepList = rep[propName].toMap();
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
			this->setProperty(propName, from);
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
		const char*   propName = mpro.name();
		QVariant      from     = this->property(propName);
		int           userType = mpro.userType();

		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			int       index = from.toInt();
			QString   to    = menum.key(index);
			rep[propName] = to;
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
				printf("VObject::load QMetaType::convert return false name=%s\n", propName); // gilgil temp 2015.01.07
				VMetaDump::dump(&from); // gilgil temp 2015.01.07
				VMetaDump::dump(&to); // gilgil temp 2015.01.07
			}
			rep[propName] = to;
		} else
		if (userType == qMetaTypeId<VObject*>())
		{
			VObject* childObj = this->property(propName).value<VObject*>();
			VRep     childRep;
			childObj->save(childRep);
			rep[propName] = childRep;
		} else
		if (userType == qMetaTypeId<VObjectList*>())
		{
			VObjectList* childObjList = this->property(propName).value<VObjectList*>();
			VRep childRepList;
			int i = 0;
			foreach (VObject* childObj, *childObjList)
			{
				VRep childRep;
				childObj->save(childRep);
				childRepList[QString::number(i)] = childRep;
				i++;
			}
			rep[propName] = childRepList;
		} else
		{
			if (!(QString(propName) == "objectName" && from == ""))
				rep[propName] = from;
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
QWidget* VObject::createWidget()
{
	VTreeWidget* tw = new VTreeWidget(NULL, this);

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
			new VTreeWidgetItemEnum(tw, i);
		} else
		if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
		{
			new VTreeWidgetItemText(tw, i);
		} else
		if (userType == qMetaTypeId<VObject*>())
		{
		} else
		if (userType == qMetaTypeId<VObjectList*>())
		{
		} else
		{
			new VTreeWidgetItemText(tw, i);
		}
	}
	return tw;
}

#endif // QT_GUI_LIB
