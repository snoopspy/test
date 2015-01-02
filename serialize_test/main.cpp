#include <QDebug>

#include "vip.h"
#include "vtcpclient.h"
#include "vlog.h"
#include "vmetaobject.h"
#include "vstate.h"

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
	log.showDateTime = VLog::DateTime;
	log.setProperty("showDateTime", VLog::None);
	qDebug() << (int)log.showDateTime;
	VMetaObject::dump(&log);
}

void stateTest()
{
	Foo foo;
	qDebug() << "sizeof(Foo)" << sizeof(foo);
	VMetaObject::dump((QMetaObject*)&Foo::staticMetaObject);
}

/*
int main()
{
	//sizeofTest();
	//ipTest();
	//tcpClientTest();
	//logTest();
	stateTest();
	return 0;
}
*/

/*
#include <QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	return a.exec();
}
*/
