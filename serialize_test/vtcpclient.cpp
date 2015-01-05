#include "vtcpclient.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(VTcpClienTest, dumpTest)
{
	VTcpClient tcpClient;
	tcpClient.ip = 0x1234;
	tcpClient.port = 80;
	VMetaObject::dump(&tcpClient);
}

#endif // GTEST
