#include <QDebug>

#include "vip.h"
#include "vtcpclient.h"
#include "vlog.h"
#include "vvariant.h"

void sizeofTest()
{
	qDebug() << "sizeof(QVariant)" << sizeof(QVariant);
	qDebug() << "sizeof(VIp)" << sizeof(VIp);
	qDebug() << "sizeof(VObject)" << sizeof(VObject);
	qDebug() << "sizeof(VTcpClient)" << sizeof(VTcpClient);
}

void ipTest()
{
	QVariant variant;
	{
		VIp ip(4);
		variant = ip;
	}
	{
		VIp ip;
		ip = variant;
		qDebug() << (quint32)ip;
	}
}

void tcpClientTest()
{
	VRep rep;
	{
		VTcpClient tcpClient;
		tcpClient.setIp(1234);
		rep << tcpClient;
	}
	{
		VTcpClient tcpClient;
		rep >> tcpClient;
		qDebug() << (quint32)tcpClient.ip();
	}
}

void logTest()
{
	VLog log;
	log.setShowDateTime(VLog::DateTime);
	// qDebug() << (int)log.showDateTime();
	VVariant::dump(&log);
}

int main()
{
	//sizeofTest();
	//ipTest();
	//tcpClientTest();
	logTest();
	return 0;
}

/*
#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	return a.exec();
}
*/
