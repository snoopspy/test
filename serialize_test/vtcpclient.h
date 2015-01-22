#ifndef VTCPCLIENT_H
#define VTCPCLIENT_H

#include "vip.h"
#include "vobject.h"

class _VTcpClient : public _VObject
{
	Q_OBJECT
  Q_PROPERTY(_VIp ip MEMBER ip)
  Q_PROPERTY(int port MEMBER port)

public:
  _VTcpClient() { ip = 0; port = 0; }

public:
	_VIp ip;
	int port;
};
//Q_DECLARE_METATYPE(_VTcpClient)

#endif // VTCPCLIENT_H
