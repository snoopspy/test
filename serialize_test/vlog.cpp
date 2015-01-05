#include "vlog.h"

#ifdef GTEST
#include <gtest/gtest.h>

TEST(VLogTest, dumpTest)
{
	VLog log;
	log.setObjectName("myLog");
	log.showDateTime = VLog::DateTime;
	VMetaObject::dump(&log);
}

#endif // GTEST
