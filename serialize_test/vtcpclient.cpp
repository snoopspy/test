#include "vtcpclient.h"
#include "vserializer.h"

#ifdef GTEST
#include <gtest/gtest.h>

class TcpClientTest : public testing::Test
{
protected:
  virtual void SetUp()
  {
    _VIp::_initialize();
    VSerializerMgr::_initialize();
  }
};

TEST_F(TcpClientTest, dumpTest)
{
  _VTcpClient tcpClient;
  tcpClient.ip = 1234;
  tcpClient.port = 80;
  VMetaDump::dump(&tcpClient);
}

TEST_F(TcpClientTest, saveLoadTest)
{
  _VTcpClient tcpClient1;
  tcpClient1.ip = 1235;
  tcpClient1.port = 80;
  tcpClient1.saveToFile("tcpClient.json");

  _VTcpClient tcpClient2;
  tcpClient2.loadFromFile("tcpClient.json");
  EXPECT_TRUE(tcpClient2.ip == 1235);
  EXPECT_TRUE(tcpClient2.port == 80);
}

#endif // GTEST
