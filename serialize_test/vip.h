#ifndef VIP_H
#define VIP_H

#include <QString>
#include "vmetaobject.h"

class VIp
{
public:
	VIp() {}

	//VIp(QVariant variant) { *this = qvariant_cast<VIp>(variant); }
	//operator QVariant() { return QVariant::fromValue<VIp>(*this); }
	//VIp(QVariant variant) { QString s = variant.toString(); m_ip = s.toUInt(); }
	//operator QVariant() { return QString::number(m_ip); }

	VIp(quint32 ip) { m_ip = ip; }
	operator quint32() { return m_ip; }

	//VIp(const QString s) { m_ip = s.toInt(); }
	//operator QString() { return QString::number(m_ip); }
	//static VIp fromString(QString s) { VIp res(s.toInt()); return res; }
	//QString toString() { return QString::number(m_ip); }

	static QString ipToString(const VIp ip);
	static VIp stringToIp(const QString s);
	static VIp variantToIp(const QVariant variant);
public:
	quint32 m_ip;
};
Q_DECLARE_METATYPE(VIp)



#endif // VIP_H
