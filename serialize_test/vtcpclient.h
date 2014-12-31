#ifndef VTCPCLIENT_H
#define VTCPCLIENT_H

#include "vip.h"
#include "vobject.h"

class VTcpClient : public VObject
{
	Q_OBJECT
	Q_PROPERTY(VIp ip READ ip WRITE setIp)

public:
	VTcpClient() {}

	V_PROPERTY_FUNC(VIp, ip, setIp, m_ip)

public:
	VIp m_ip;
};

#endif // VTCPCLIENT_H
