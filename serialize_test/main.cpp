#include <QApplication>

#include "vtcpclient.h"
_VObject* createTcpClient()
{
	_VIp::_initialize();
  _VTcpClient* tcpClient = new _VTcpClient;
	tcpClient->setObjectName("tcpClient1");
	tcpClient->ip = 1111;
	tcpClient->port = 222;
	return tcpClient;
}

#include "other.h"
_VObject* createNestedClient()
{
	NestedClient* nc = new NestedClient;
	nc->setObjectName("nestedClient1");
	nc->tcpClient.setObjectName("tcpClient1");
	return nc;
}

#include "vlog.h"
_VObject* createLog()
{
	_VLog* log = new _VLog;
	log->setObjectName("log1");
	return log;
}

_VObject* createNetInfo()
{
	VNetInfo* netInfo = new VNetInfo;
  netInfo->setObjectName("newInfo1");
	netInfo->ip = 1111;
	netInfo->mac = QString("abcdef");
	return netInfo;
}

_VObject* createObjList()
{
	ObjList* objList = new ObjList;
	objList->setObjectName("objList1");
  objList->tcpClientList.append(new _VTcpClient);
  objList->tcpClientList.append(new _VTcpClient);
	return objList;
}

#include "vserializer.h"
int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	_VIp::_initialize();
	_VMac::_initialize();
  VSerializerMgr::_initialize();

  //_VObject* object = createLog();
  //_VObject* object = createTcpClient();
  //_VObject* object = createNestedClient();
  //_VObject* object = createNetInfo();
  _VObject* object = createObjList();

  QWidget* widget = object->createWidget(NULL);
  widget->show();
	int res = a.exec();
  delete widget;
	delete object;
	return res;
}
