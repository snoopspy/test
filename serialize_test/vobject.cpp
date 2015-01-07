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
			VObject* childObj = qvariant_cast<VObject*>(this->property(name));
			VRep     childRep = rep[name].toMap();
			childObj->load(childRep);
		} else
		if (userType == qMetaTypeId<VObjectList>())
		{
			VObjectList childObjList = qvariant_cast<VObjectList>(this->property(name));
			VRep childRepList = rep[name].toMap();
			printf("%d\n", childRepList.count()); // gilgil temp 2015.01.07
			for (VRep::iterator it = childRepList.begin(); it != childRepList.end(); it++)
			{
				VRep childRep = it->toMap();
				QString className = childRep["_class"].toString();
				int id = QMetaType::type(qPrintable(className)); // gilgil temp 2015.01.07
				//int id = QMetaType::type("VObject");
				if (id == QMetaType::UnknownType) {
					printf("can not resolve type for class %s\n", qPrintable(className));
					continue;
				}
				void* obj = QMetaType::create(id);
				VObject* vobj = (VObject*)obj;
				//VObject* vobj = qvariant_cast<VObject*>(QMetaType::create(id));
				vobj->load(childRep);
				childObjList.push_back(vobj);
			}
			//this->setProperty(name, childObjList);
		} else
		{
			this->setProperty(name, from);
		}
	}
	QString className = rep["_class"].toString();
	if (className != this->metaObject()->className())
	{
		printf("different class name (%s) and (%s)", qPrintable(className), this->metaObject()->className());
	}
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
			VObject* childObj = qvariant_cast<VObject*>(this->property(name));
			VRep     childRep;
			childObj->save(childRep);
			rep[name] = childRep;
		} else
		if (userType == qMetaTypeId<VObjectList>())
		{
			VObjectList childObjList = qvariant_cast<VObjectList>(this->property(name));
			VRep childRepList;
			int i = 0;
			foreach (VObject* childObj, childObjList)
			{
				VRep ChildRep;
				childObj->save(ChildRep);
				childRepList[QString::number(i)] = ChildRep;
				i++;
			}
			rep[name] = childRepList;
		} else
		{
			rep[name] = from;
		}
	}
	rep["_class"] = this->metaObject()->className();
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
