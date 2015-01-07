#include <stdio.h> // for printf
#include <QMetaProperty>
#include "vmetadump.h"
#include "vstrrep.h"

VRep VStrRep::repToStrRep(const VRep& rep, const QMetaObject* mobj)
{
	VRep strRep;
	int count = mobj->propertyCount();
	for (int i = 0; i < count; i++)
	{
		QMetaProperty mpro  = mobj->property(i);
		const char* proName = mpro.name();
		QMap<QString, QVariant>::const_iterator it = rep.find(proName);
		if (it == rep.end()) continue;

		QString  key  = it.key();
		QVariant from = it.value();
		QVariant to   = QVariant(QVariant::String, NULL);

		if (QMetaType::hasRegisteredConverterFunction(from.userType(), to.userType()))
		//if (mpro.type() == QVariant::UserType)
		{
			void* fromData     = from.data();
			int   fromUserType = from.userType();
			void* toData       = to.data();
			int   toUserType   = to.userType(); // QVariant::String
			bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
			if (!res)
			{
				printf("VObject::save QMetaType::convert return false proName=%s\n", proName);
				VMetaDump::dump(&from);
				to = from;  // gilgil temp 2014.01.06
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
		strRep.insert(key, to);
	}
	return strRep;
}

VRep VStrRep::strReptoRep(const VRep& strRep, const QMetaObject* mobj)
{
	VRep rep;
	int count = mobj->propertyCount();
	for (int i = 0; i < count; i++)
	{
		QMetaProperty mpro = mobj->property(i);
		const char* proName = mpro.name();
		QMap<QString, QVariant>::const_iterator it = strRep.find(proName);
		if (it == strRep.end()) continue;

		QString  key  = it.key();
		QVariant from = it.value();
		QVariant to   = QVariant(mpro.userType(), NULL);

		if (QMetaType::hasRegisteredConverterFunction(from.userType(), to.userType()))
		//if (mpro.type() == QVariant::UserType)
		{
			void* fromData     = from.data();
			int   fromUserType = from.userType(); // QVariant::String
			void* toData       = to.data();
			int   toUserType   = to.userType();
			bool res = QMetaType::convert(fromData, fromUserType, toData, toUserType);
			if (!res)
			{
				printf("VObject::load QMetaType::convert return false proName=%s\n", proName);
				VMetaDump::dump(&from);
				VMetaDump::dump(&to);
				to = from; // gilgil temp 2014.01.06
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
		rep.insert(key, to);
	}
	return rep;
}
