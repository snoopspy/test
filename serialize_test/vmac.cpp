#include "vmac.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(VMacTest, commonTest)
{
	_VMac mac = QString("123456");
	QString s = mac;
	printf("%s\n", qPrintable(s));
}

#endif // GTEST
