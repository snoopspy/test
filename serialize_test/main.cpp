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

VObject* createNetInfo()
{
	VNetInfo* netInfo = new VNetInfo;
	netInfo->ip = 1111;
	netInfo->mac = QString("abcdef");
	return netInfo;
}

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	VIp::registerConverter();
	VMac::registerConverter();

	//VObject* object = createTcpClient();
	//VObject* object = createLog();
	//VObject* object = createNestedClient();
	VObject* object = createNetInfo();
	//VObject* object = new ObjList;

	VTreeWidget* treeWidget = new VTreeWidget(NULL, object);
	QTreeWidgetItem* item = new QTreeWidgetItem(treeWidget);
	item->setText(1, "1");
	item = new QTreeWidgetItem(treeWidget);
	item->setText(1, "2");
	item = new QTreeWidgetItem(treeWidget);
	item->setText(1, "3");
	//QTreeWidgetItem* item = treeWidget->itemAt(0, 0);
	//QTreeWidgetItem* newItem = new QTreeWidgetItem(item);
	//QTreeWidgetItem* newItem = new QTreeWidgetItem(treeWidget, item);
	//QTreeWidgetItem* newItem = new QTreeWidgetItem(item);
	//newItem->setText(1, "test");
	treeWidget->expandAll();
	treeWidget->show();
	int res = a.exec();
	delete object;
	delete treeWidget;
	return res;
}

