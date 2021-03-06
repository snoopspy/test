#include "vlog.h"

#ifdef GTEST
#include <gtest/gtest.h>
#include <QJsonObject>

TEST(VLogTest, sizeTest)
{
  printf("sizeof(_VLog) is %zu\n", sizeof(VLog));
}

TEST(VLogTest, dumpTest)
{
  VLog log;
  log.showDateTime = VLog::DateTime;
  VMetaDump::dump(&log);
}

TEST(VLogTest, saveLoadTest)
{
  VLog log;
  log.showDateTime = VLog::DateTime;
  log.saveToFile("log.json");

  VLog newLog;
  newLog.loadFromFile("log.json");
  EXPECT_TRUE(newLog.showDateTime == VLog::DateTime);
}

#endif // GTEST
