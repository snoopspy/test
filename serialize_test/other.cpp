#include "other.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(NestedClientTest, commonTest)
{
	VIp::registerConverter();

	NestedClient nc;
	nc.tcpClient.ip = 1111;
	nc.tcpClient.port = 81;
	VMetaDump::dump(&nc);
	nc.saveToFile("nc.json");

	NestedClient nc2;
	nc2.loadFromFile("nc.json");
	EXPECT_TRUE(nc2.tcpClient.ip == 1111);
	EXPECT_TRUE(nc2.tcpClient.port == 81);
}

#endif // GTEST
