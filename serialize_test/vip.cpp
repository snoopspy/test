#include "vip.h"
#include "vrep.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(VIpTest, sizeTest)
{
  printf("sizeof(_VIp) is %zu\n", sizeof(_VIp));
  EXPECT_TRUE(sizeof(_VIp) == sizeof(quint32));
}

TEST(VIpTest, varTest)
{
  _VIp ip = 1234;
  QVariant var = QVariant::fromValue<_VIp>(ip);
  VMetaDump::dump(&var);

  int userType = var.userType();
  EXPECT_TRUE(userType == qMetaTypeId<_VIp>());

  QVariant::Type type = var.type();
  EXPECT_TRUE((int)type == QMetaType::User);

  QString typeName = var.typeName();
  EXPECT_TRUE(typeName == "_VIp");
}

TEST(VIpTest, varCopyTest)
{
  _VIp ip1 = 1234;
  QVariant variant = QVariant::fromValue<_VIp>(ip1);
  _VIp ip2 = variant.value<_VIp>();
  EXPECT_TRUE(ip2 == 1234);
}

TEST(VIpTest, copyTest)
{
  _VIp ip1(1234);
  _VIp ip2 = ip1;
  EXPECT_TRUE(ip2 == 1234);
}

TEST(VIpTest, addTest)
{
  _VIp ip1(1111);
  _VIp ip2(2222);
  _VIp ip3 = ip1 + ip2;
  EXPECT_TRUE(ip3 == 3333);
}

#endif // GTEST
