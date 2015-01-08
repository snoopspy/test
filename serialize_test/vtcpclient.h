#ifndef VTCPCLIENT_H
#define VTCPCLIENT_H

#include "vip.h"
#include "vobject.h"

class VTcpClient : public VObject
{
	Q_OBJECT

public:
	VIp ip;
	int port;

public:
	Q_PROPERTY(VIp ip MEMBER ip)
	Q_PROPERTY(int port MEMBER port)

};
//Q_DECLARE_METATYPE(VTcpClient)

#endif // VTCPCLIENT_H
