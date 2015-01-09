#include <QApplication>

#include "vtcpclient.h"
VObject* createTcpClient()
{
	VIp::registerConverter();
	VTcpClient* tcpClient = new VTcpClient;
	tcpClient->ip = 1111;
	tcpClient->port = 222;
	return tcpClient;
}

#include "other.h"
VObject* createNestedClient()
{
	NestedClient* nc = new NestedClient;
	return nc;
}

#include "vlog.h"
VObject* createLog()
{
	VLog* log = new VLog;
	return log;
}

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	VIp::registerConverter();

	VObject* object = createTcpClient();
	//VObject* object = createLog();

	QWidget* widget = object->createWidget();
	widget->show();
	int res = a.exec();
	delete object;
	delete widget;
	return res;
}
