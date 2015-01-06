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
		QMetaProperty mpro = mobj->property(i);
		const char* name = mpro.name();

		QVariant from = rep[name];

		QVariant to = this->property(name);

		QVariant::Type toType = to.type();
		if (toType == QVariant::UserType)
		{
			void* fromData = from.data();
			int fromUserType = from.userType();
			void* toData = to.data();
			int toUserType = to.userType();
			bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
			if (!res)
			{
				printf("VObject::load QMetaType::convert return false\n");
				VMetaDump::dump(&from);
				VMetaDump::dump(&to);
				to = from;
			}
		} else
		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			QString keys = from.toString();
			to = menum.keysToValue(qPrintable(keys));
		} else {
			to = from;
		}
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

		QVariant to;
		if (fromType == QVariant::UserType)
		{
			void* fromData = from.data();
			int fromUserType = from.userType();
			void* toData = to.data();
			int toUserType = QVariant::String;
			bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
			if (!res)
			{
				printf("VObject::save QMetaType::convert return false\n");
				VMetaDump::dump(&from);
				to = from;
			}
		} else
		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			int index = from.toInt();
			to = menum.key(index);
		} else {
			to = from;
		}
		rep[name] = to;
	}
}
