#ifndef VTCPCLIENT_H
#define VTCPCLIENT_H

#include "vip.h"
#include "vobject.h"

class VTcpClient : public VObject
{
	Q_OBJECT
	//Q_PROPERTY(VIp ip READ ip WRITE setIp)
	Q_PROPERTY(VIp ip MEMBER ip)
	Q_PROPERTY(int port MEMBER port)

public:
	explicit VTcpClient() {}

	//V_PROPERTY_FUNC(VIp, ip, setIp, m_ip)

public:
	VIp ip;
	int port;
};

#endif // VTCPCLIENT_H
