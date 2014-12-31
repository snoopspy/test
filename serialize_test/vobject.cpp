#include <QMetaObject>
#include <QMetaProperty>

#include "vobject.h"

void VObject::load(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int cnt = mobj->propertyCount();
	for (int i = 0; i < cnt; i++)
	{
		QMetaProperty mpro = mobj->property(i);
		const char* name = mpro.name();
		QVariant value = rep[name];
		this->setProperty(name, value);
	}
}

void VObject::save(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int cnt = mobj->propertyCount();
	for (int i = 0; i < cnt; i++)
	{
		QMetaProperty mpro = mobj->property(i);
		const char* name = mpro.name();
		QVariant value = this->property(name);
		rep.insert(QString(name), value);
	}
}
