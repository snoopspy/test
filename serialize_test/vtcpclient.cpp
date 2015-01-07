#include "vtcpclient.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(VTcpClientTest, dumpTest)
{
	VIp::registerConverter();
	VTcpClient tcpClient;
	tcpClient.ip = 1234;
	tcpClient.port = 80;
	VMetaDump::dump(&tcpClient);
}

TEST(VTcpClientTest, saveTest)
{
	VIp::registerConverter();
	VTcpClient tcpClient1;
	tcpClient1.ip = 1235;
	tcpClient1.port = 80;
	tcpClient1.saveToFile("tcpClient.json");

	VTcpClient tcpClient2;
	tcpClient2.loadFromFile("tcpClient.json");
	EXPECT_TRUE(tcpClient2.ip == 1235);
	EXPECT_TRUE(tcpClient2.port == 80);
}

TEST(NestedClientTest, commonTest)
{
	NestedClient nc;
	VMetaDump::dump(&nc);
	nc.saveToFile("nc.json");
}

#endif // GTEST
