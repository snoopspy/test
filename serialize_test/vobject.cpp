#include <QDebug>
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
		QVariant from = rep[name];
		QVariant to = this->property(name);
		QVariant::Type toType = to.type();
		if (toType != QVariant::UserType)
			to = from;
		else
			QMetaType::convert(from.data(), from.type(), to.data(), to.type());
		this->setProperty(name, to);
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
		QVariant from = this->property(name);
		QVariant::Type fromType = from.type();
		QVariant to = from;
		if (fromType != QVariant::UserType)
			to = from;
		else
			QMetaType::convert(from.data(), from.type(), to.data(), to.type());
		rep[name] = to;
	}
}
