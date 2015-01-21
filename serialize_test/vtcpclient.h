#ifndef VTCPCLIENT_H
#define VTCPCLIENT_H

#include "vip.h"
#include "vobject.h"

class VTcpClient : public VObject
{
	Q_OBJECT
  Q_PROPERTY(VIp ip MEMBER ip)
  Q_PROPERTY(int port MEMBER port)

public:
	VTcpClient() { ip = 0; port = 0; }

public:
	VIp ip;
	int port;
};
//Q_DECLARE_METATYPE(VTcpClient)

#endif // VTCPCLIENT_H
