#ifndef VIP_H
#define VIP_H

#include <stdio.h>
#include <QString>
#include "vmetadump.h"

class VIp
{
	// Q_GADGET

public:
	VIp() {}

	//VIp(QVariant variant) { *this = qvariant_cast<VIp>(variant); }
	//operator QVariant() { return QVariant::fromValue<VIp>(*this); }

	VIp(quint32 ip) { m_ip = ip; }
	operator quint32() { return m_ip; }

	static QString toString(const VIp& ip) { return QString::number(ip.m_ip);}
	static VIp fromString(const QString& s) { return VIp(s.toUInt()); }

	static void registerConverter()
	{
		static bool registered = false;
		if (!registered)
		{
			bool res;
			res = QMetaType::registerConverter<VIp, QString>(VIp::toString);
			if (!res)
			{
				printf("QMetaType::registerConverter<VIp, QString>(VIp::ipToString) return false\n");
			}
			res = QMetaType::registerConverter<QString, VIp>(VIp::fromString);
			if (!res)
			{
				printf("QMetaType::registerConverter<QString, VIp>(VIp::stringToIp) return false\n");
			}
			/*
			VIp ip1(1234);
			QVariant variant = QVariant::fromValue<VIp>(ip1);
			VIp ip2 = qvariant_cast<VIp>(variant);
			*/
			registered = true;
		}
	}
public:
	quint32 m_ip;
};
Q_DECLARE_METATYPE(VIp)

#endif // VIP_H
