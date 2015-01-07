#include "other.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(NestedClientTest, saveLoadTest)
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
	VIp::registerConverter();
	qRegisterMetaType<VTcpClient>("VTcpClient"); // gilgil temp 2015.01.07

	ObjList ol;
	VTcpClient* tcpClient;
	tcpClient = new VTcpClient;
	tcpClient->ip = 1111;
	tcpClient->port = 1111;
	ol.objList.push_back(tcpClient);

	tcpClient = new VTcpClient;
	tcpClient->ip = 2222;
	tcpClient->port = 2222;
	ol.objList.push_back(tcpClient);

	tcpClient = new VTcpClient;
	tcpClient->ip = 3333;
	tcpClient->port = 3333;
	ol.objList.push_back(tcpClient);

	ol.saveToFile("ol.json");

	ObjList ol2;
	ol2.loadFromFile("ol.json");
	EXPECT_TRUE(ol2.objList.count() == 3);
}


#endif // GTEST
