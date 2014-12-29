#ifndef VIP_H
#define VIP_H

#include "vvar.h"

class VIp
{
public:
	VIp() {}
	VIp(const VIp& rhs) { m_ip = rhs.m_ip; }
	VIp(quint32 ip) { m_ip = ip; }
	VIp(QVariant variant) { m_ip = variant.toUInt(); }
	~VIp() {}
	operator quint32() { return m_ip; }
	operator QVariant() { return (QVariant)m_ip; }
private:
	quint32 m_ip;
};
Q_DECLARE_METATYPE(VIp)

#endif // VIP_H
