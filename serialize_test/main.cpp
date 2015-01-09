#include <QApplication>

#include "vtcpclient.h"
VObject* createTcpClient()
{
	VIp::registerConverter();
	VTcpClient* tcpClient = new VTcpClient;
	tcpClient->setObjectName("tcpClient");
	tcpClient->ip = 1111;
	tcpClient->port = 222;
	return tcpClient;
}

#include "other.h"
VObject* createNestedClient()
{
	NestedClient* nc = new NestedClient;
	nc->setObjectName("nc");
	nc->tcpClient.setObjectName("tc");
	//nc->tcpClientsetObjectName("tc");
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

	//VObject* object = createTcpClient();
	//VObject* object = createLog();
	VObject* object = createNestedClient();

	VTreeWidget* treeWidget = new VTreeWidget(NULL, object);
	object->createTreeWidgetItems(treeWidget, NULL);
	QTreeWidgetItem* item = treeWidget->itemAt(0, 0);
	//QTreeWidgetItem* newItem = new QTreeWidgetItem(item);
	//QTreeWidgetItem* newItem = new QTreeWidgetItem(treeWidget, item);
	//QTreeWidgetItem* newItem = new QTreeWidgetItem(item);
	//newItem->setText(1, "test");
	treeWidget->show();
	int res = a.exec();
	delete object;
	delete treeWidget;
	return res;
}

