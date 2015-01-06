#include "vtcpclient.h"
#include <QDebug>

#ifdef GTEST
#include <gtest/gtest.h>

TEST(VTcpClienTest, dumpTest)
{
	VTcpClient tcpClient;
	tcpClient.ip = 0x1234;
	tcpClient.port = 80;
	QMetaType::registerConverter<VIp, QString>(VIp::ipToString);
	VMetaObject::dump(&tcpClient);
}

TEST(VTcpClienTest, saveTest)
{
	VTcpClient tcpClient;
	tcpClient.ip = 0x1235;
	tcpClient.port = 80;
	VIp::initialize();
	tcpClient.saveToFile("tcpClient.json");
	{
		VTcpClient newTcpClient;
		newTcpClient.ip.m_ip = 0;
		newTcpClient.loadFromFile("tcpClient.json");
		qDebug() << newTcpClient.ip.m_ip;
		qDebug() << newTcpClient.port;
	}
}

#endif // GTEST
