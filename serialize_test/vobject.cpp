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
		QVariant sValue = rep[name].toString();
		QVariant value = this->property(name);
		QVariant::Type valueType = value.type();
		if (valueType == QVariant::UserType)
		{
			void* valueData = value.data();
			int valueUserType = value.userType();
			void* sValueData = sValue.data();
			int sValueUserType = sValue.userType();
			bool res = QMetaType::convert(sValueData, sValueUserType, valueData, valueUserType);
			if (!res)
			{
				printf("VObject::load QMetaType::convert return false name=%s\n", name);
				VMetaDump::dump(&sValue);
				VMetaDump::dump(&value);
				value = sValue; // gilgil temp 2014.01.06
			}
		} else
		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			QString keys = sValue.toString();
			value = menum.keysToValue(qPrintable(keys));
		} else {
			value = sValue;
		}
		this->setProperty(name, value);
	}
}

void VObject::save(VRep& rep)
{
	const QMetaObject *mobj = this->metaObject();
	int cnt = mobj->propertyCount();
	for (int i = 0; i < cnt; i++)
	{
		QMetaProperty mpro       = mobj->property(i);
		const char* name         = mpro.name();
		QVariant value           = this->property(name);
		QVariant::Type valueType = value.type();
		QVariant sValue          = "";
		if (valueType == QVariant::UserType)
		{
			void* valueData      = value.data();
			int   valueUserType  = value.userType();
			void* sValueData     = sValue.data();
			int   sValueUserType = sValue.userType();
			bool res = QMetaType::convert(valueData, valueUserType, sValueData, sValueUserType);
			if (!res)
			{
				printf("VObject::save QMetaType::convert return false name=%s\n", name);
				VMetaDump::dump(&value);
				sValue = value;  // gilgil temp 2014.01.06
			}
		} else
		if (mpro.isEnumType())
		{
			QMetaEnum menum = mpro.enumerator();
			int index = value.toInt();
			sValue = menum.key(index);
		} else {
			sValue = value;
		}
		rep[name] = sValue;
	}
}
