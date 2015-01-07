#include <QDebug>
#include <QMetaEnum>
#include <QMetaObject>
#include <QMetaProperty>

#include "vmetadump.h"
#include "vobject.h"

void VObject::load(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int cnt = mobj->propertyCount();
	for (int i = 0; i < cnt; i++)
	{
		QMetaProperty mpro  = mobj->property(i);
		const char*   name  = mpro.name();
		QVariant      value = rep[name];
		this->setProperty(name, value);
	}
}

void VObject::save(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int cnt = mobj->propertyCount();
	for (int i = 0; i < cnt; i++)
	{
		QMetaProperty mpro  = mobj->property(i);
		const char*   name  = mpro.name();
		QVariant      value = this->property(name);
		rep[name] = value;
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
