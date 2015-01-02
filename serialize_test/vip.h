#ifndef VIP_H
#define VIP_H

#include "vmetaobject.h"

class VIp
{
public:
	VIp() {}
	V_QVAR_CONVERSION(VIp)
	V_TYPE_CONVERSION(VIp, quint32, m_ip)

private:
	quint32 m_ip;
};
Q_DECLARE_METATYPE(VIp)

#endif // VIP_H
