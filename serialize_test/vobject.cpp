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
	for (int propIndex = 0; propIndex < count; propIndex++)
	{
		QMetaProperty mpro      = mobj->property(propIndex);
		const char*   propName  = mpro.name();
		QVariant      propValue = rep[propName];
		int           userType  = mpro.userType();

		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			QString   key   = propValue.toString();
			QVariant  to    = menum.keyToValue(qPrintable(key));
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
				VObject* vobj = childObjList->createObject();
				vobj->load(childRep);
				childObjList->push_back(vobj);
			}
		} else
		if (QMetaType::hasRegisteredConverterFunction(QVariant::String, userType))
		{
			QVariant to = convert(propValue, userType);
			this->setProperty(propName, to);
		} else
		{
			this->setProperty(propName, propValue);
		}
	}
}

void VObject::save(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int count = mobj->propertyCount();
	for (int propIndex = 0; propIndex < count; propIndex++)
	{
		QMetaProperty mpro      = mobj->property(propIndex);
		const char*   propName  = mpro.name();
		QVariant      propValue = this->property(propName);
		int           userType  = mpro.userType();

		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			int       index = propValue.toInt();
			QString   to    = menum.key(index);
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
		if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
		{
			QVariant to = convert(propValue, QVariant::String);
			rep[propName] = to;
		} else
		{
			if (!(QString(propName) == "objectName" && propValue == ""))
				rep[propName] = propValue;
		}
	}
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

QVariant VObject::convert(QVariant from, int type)
{
	QVariant to(type, NULL);

	void* fromData     = from.data();
	int   fromUserType = from.userType();
	void* toData       = to.data();
	int   toUserType   = to.userType();
	bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
	if (!res)
	{
		printf("VObject::load QMetaType::convert return false\n"); // gilgil temp 2015.01.07
		VMetaDump::dump(&from); // gilgil temp 2015.01.07
		VMetaDump::dump(&to); // gilgil temp 2015.01.07
	}
	return to;
}

#ifdef QT_GUI_LIB
void VObject::createTreeWidgetItems(VTreeWidget* treeWidget, VTreeWidgetItem* parent)
{
	const QMetaObject *mobj = this->metaObject();
	int count = this->metaObject()->propertyCount();

	//for (int i = count - 1; i >= 0; i--) // gilgil temp
	for (int propIndex = 0; propIndex < count; propIndex++)
	{
		QMetaProperty mpro     = mobj->property(propIndex);
		const char*   propName = mpro.name();
		// QVariant      from     = this->property(propName); // gilgil temp
		int           userType = mpro.userType();

		if (mpro.isEnumType())
		{
			new VTreeWidgetItemEnum(treeWidget, parent, this, propIndex);
		} else
		if (userType == qMetaTypeId<VObject*>())
		{
			VTreeWidgetItem* item = new VTreeWidgetItem(treeWidget, parent, this, propIndex);
			VObject* childObj = this->property(propName).value<VObject*>();
			childObj->createTreeWidgetItems(NULL, item);
		} else
		if (userType == qMetaTypeId<VObjectList*>())
		{
		} else
		if (QMetaType::hasRegisteredConverterFunction(userType, QVariant::String))
		{
			new VTreeWidgetItemText(treeWidget, parent, this, propIndex);
		} else
		{
			new VTreeWidgetItemText(treeWidget, parent, this, propIndex);
		}
	}
}

#endif // QT_GUI_LIB
