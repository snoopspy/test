#include <QApplication>

#include "vtcpclient.h"
VObject* createTcpClient()
{
	VIp::registerConverter();
	VTcpClient* tcpClient = new VTcpClient;
	tcpClient->setObjectName("tcpClient1");
	tcpClient->ip = 1111;
	tcpClient->port = 222;
	return tcpClient;
}

#include "other.h"
VObject* createNestedClient()
{
	NestedClient* nc = new NestedClient;
	nc->setObjectName("nestedClient1");
	nc->tcpClient.setObjectName("tcpClient1");
	return nc;
}

#include "vlog.h"
VObject* createLog()
{
	VLog* log = new VLog;
	log->setObjectName("log1");
	return log;
}

VObject* createNetInfo()
{
	VNetInfo* netInfo = new VNetInfo;
	netInfo->ip = 1111;
	netInfo->mac = QString("abcdef");
	return netInfo;
}

VObject* createObjList()
{
	ObjList* objList = new ObjList;
	objList->setObjectName("objList1");
	objList->tcpClientList.append(new VTcpClient);
	//objList->tcpClientList.append(new VTcpClient);
	return objList;
}

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	VIp::registerConverter();
	VMac::registerConverter();

	//VObject* object = createLog();
	//VObject* object = createTcpClient();
	VObject* object = createNestedClient();
	//VObject* object = createNetInfo();
	//VObject* object = createObjList();
//
	VTreeWidget* treeWidget = new VTreeWidget(NULL, object);
	//object->createTreeWidgetItems((VTreeWidgetItem*)treeWidget->topLevelItem(0));

	//QTreeWidgetItem* item = treeWidget->itemAt(0, 0);
	//QTreeWidgetItem* newItem = new QTreeWidgetItem(item);
	//QTreeWidgetItem* newItem = new QTreeWidgetItem(treeWidget, item);
	//QTreeWidgetItem* newItem = new QTreeWidgetItem(item);
	//newItem->setText(1, "test");
	//treeWidget->expandAll();
	treeWidget->show();
	int res = a.exec();
	delete treeWidget;
	delete object;
	return res;
}

