#include "vip.h"
#include "vrep.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(VIpTest, sizeTest)
{
  printf("sizeof(VIp) is %zu\n", sizeof(VIp));
  EXPECT_TRUE(sizeof(VIp) == sizeof(quint32));
}

TEST(VIpTest, varTest)
{
  VIp ip = 1234;
  QVariant var = QVariant::fromValue<VIp>(ip);
  VMetaDump::dump(&var);

  int userType = var.userType();
  EXPECT_TRUE(userType == qMetaTypeId<VIp>());

  QVariant::Type type = var.type();
  EXPECT_TRUE((int)type == QMetaType::User);

  QString typeName = var.typeName();
  EXPECT_TRUE(typeName == "VIp");
}

TEST(VIpTest, varCopyTest)
{
  VIp ip1 = 1234;
  QVariant variant = QVariant::fromValue<VIp>(ip1);
  VIp ip2 = variant.value<VIp>();
  EXPECT_TRUE(ip2 == 1234);
}

TEST(VIpTest, copyTest)
{
  VIp ip1(1234);
  VIp ip2 = ip1;
  EXPECT_TRUE(ip2 == 1234);
}

TEST(VIpTest, addTest)
{
  VIp ip1(1111);
  VIp ip2(2222);
  VIp ip3 = ip1 + ip2;
  EXPECT_TRUE(ip3 == 3333);
}

#endif // GTEST
