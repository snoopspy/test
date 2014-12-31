#ifndef VIP_H
#define VIP_H

#include "vvar.h"

class VIp
{
public:
	V_TYPE_CONVERSION(VIp, quint32, m_ip)
	V_QVAR_CONVERSION(VIp)

public:
	VIp() { m_ip = -1; }

private:
	quint32 m_ip;
};
Q_DECLARE_METATYPE(VIp)

#endif // VIP_H
