#include "other.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(NestedClientTest, saveLoadTest)
{
	VIp::_initialize();

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

TEST(VNetInfoTest, saveLoadTest)
{
	VIp::_initialize();
	VMac::_initialize();

	VNetInfo netInfo;
	netInfo.ip = 1111;
	netInfo.mac = QString("123456");
	netInfo.saveToFile("ni.json");
}

TEST(IntListTest, saveLoadTest)
{
	IntList il;
	il.intList.push_back(1);
	il.intList.push_back(2);
	il.intList.push_back(3);
	il.saveToFile("il.json");

	IntList il2;
	il2.loadFromFile("il.json");
	EXPECT_TRUE(il2.intList.count() == 3);
}

TEST(ObjListTest, saveLoadTest)
{
	VIp::_initialize();

	ObjList ol;
	VTcpClient* tcpClient;
	tcpClient = new VTcpClient;
	tcpClient->ip = 1111;
	tcpClient->port = 1111;
	ol.tcpClientList.push_back(tcpClient);

	tcpClient = new VTcpClient;
	tcpClient->ip = 2222;
	tcpClient->port = 2222;
	ol.tcpClientList.push_back(tcpClient);

	tcpClient = new VTcpClient;
	tcpClient->ip = 3333;
	tcpClient->port = 3333;
	ol.tcpClientList.push_back(tcpClient);

	ol.saveToFile("ol.json");

	ObjList ol2;
	ol2.loadFromFile("ol.json");
	EXPECT_TRUE(ol2.tcpClientList.count() == 3);

	int expect = 0;
	int count = ol2.tcpClientList.count();
	for (int i = 0; i < count; i++)
	{
		VObject* obj = ol2.tcpClientList.at(i);
		EXPECT_TRUE(obj != NULL);
		VTcpClient* tcpClient = dynamic_cast<VTcpClient*>(obj);
		EXPECT_TRUE(tcpClient != NULL);
		expect += 1111;
		EXPECT_TRUE(tcpClient->ip == (quint32)expect);
		EXPECT_TRUE(tcpClient->port == expect);
	}
}

#endif // GTEST
