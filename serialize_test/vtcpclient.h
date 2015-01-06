#ifndef VTCPCLIENT_H
#define VTCPCLIENT_H

#include "vip.h"
#include "vobject.h"

class VTcpClient : public VObject
{
	Q_OBJECT
	//Q_PROPERTY(QString ip READ getIp WRITE setIp)
	Q_PROPERTY(VIp ip MEMBER ip)
	Q_PROPERTY(int port MEMBER port)

public:
	VTcpClient() {}

	//V_PROPERTY_FUNC(VIp, ip, setIp, m_ip)
	//QString getIp() { return ip.toString(); }
	//void setIp(QString s) { ip = VIp::fromString(s); };

public:
	VIp ip;
	int port;
};

class NestedClient : public VObject
{
	Q_OBJECT
	Q_PROPERTY(VTcpClient* tcpClient READ getTcpClient WRITE setTcpClient)
public:
	NestedClient() : VObject(NULL)
	{
	}
	VTcpClient* getTcpClient()
	{
		return &tcpClient;
	}
	void setTcpClient(VTcpClient* tcpClient)
	{

	}

	VTcpClient tcpClient;
};

#endif // VTCPCLIENT_H
