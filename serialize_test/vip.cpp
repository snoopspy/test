#include <QDebug>

#include "vip.h"
#include "vrep.h"

#ifdef GTEST
#include <gtest/gtest.h>

class VIpTest : public ::testing::Test
{
public:
	QVariant variant;
};

TEST_F(VIpTest, commonTest)
{
	qDebug() << "sizeof(VIp)" << sizeof(VIp);
}

TEST_F(VIpTest, saveTest)
{
	VIp ip = 1234;
	variant = ip;
	qDebug() << "type" << variant.type();
	qDebug() << "userType" << variant.userType();
	qDebug() << "typeName" << variant.typeName();
	ASSERT_EQ(strcmp(variant.typeName(), "VIp"), 0);
}

TEST_F(VIpTest, loadTest)
{
	VIp newIp = variant;
	ASSERT_TRUE(newIp == 1234);
}

#endif // GTEST
