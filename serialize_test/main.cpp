#include <QApplication>
#include "vtcpclient.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	VIp::registerConverter();
	VTcpClient tcpClient;
	tcpClient.ip = 1111;
	tcpClient.port = 222;
	VWidget* widget = tcpClient.createWidget();
	widget->show();
	return a.exec();
}
