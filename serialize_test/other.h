#ifndef OTHER_H
#define OTHER_H

#include "vtcpclient.h"

class NestedClient : public VObject
{
	Q_OBJECT
	Q_PROPERTY(VObject* tcpClient READ getTcpClient)
public:
	NestedClient() : VObject(NULL)
	{
	}
	VObject* getTcpClient()
	{
		return &tcpClient;
	}
	VTcpClient tcpClient;
};

#endif // OTHER_H
