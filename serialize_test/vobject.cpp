#include <QDebug>
#include <QMetaEnum>
#include <QMetaObject>
#include <QMetaProperty>

#include "vmetadump.h"
#include "vobject.h"
#include "vstrrep.h"

void VObject::load(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int cnt = mobj->propertyCount();
	for (int i = 0; i < cnt; i++)
	{
		QMetaProperty mpro     = mobj->property(i);
		const char*   name     = mpro.name();
		int           userType = mpro.userType();
		if (userType == qMetaTypeId<VObject*>())
		{
			VObject* childObj = qvariant_cast<VObject*>(this->property(name));
			VRep     childStrRep = rep[name].toMap();
			VRep     childRep = VStrRep::strReptoRep(childStrRep, childObj->metaObject());
			childObj->load(childRep);
		} else
		{
			QVariant value = rep[name];
			this->setProperty(name, value);
		}
	}
}

void VObject::save(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int cnt = mobj->propertyCount();
	for (int i = 0; i < cnt; i++)
	{
		QMetaProperty mpro     = mobj->property(i);
		const char*   name     = mpro.name();
		int           userType = mpro.userType();
		if (userType == qMetaTypeId<VObject*>())
		{
			VObject* childObj = qvariant_cast<VObject*>(this->property(name));
			VRep     childRep;
			childObj->save(childRep);
			VRep     childStrRep = VStrRep::repToStrRep(childRep, childObj->metaObject());
			rep[name] = childStrRep;
		} else
		{
			QVariant value = this->property(name);
			rep[name] = value;
		}
	}
}

bool VObject::loadFromFile(QString fileName)
{
	return VSerializable::loadFromFile(fileName, this->metaObject());
}

bool VObject::saveToFile(QString fileName)
{
	return VSerializable::saveToFile(fileName, this->metaObject());
}
