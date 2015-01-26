#include "vlog.h"

#ifdef GTEST
#include <gtest/gtest.h>
#include <QJsonObject>

TEST(VLogTest, sizeTest)
{
  printf("sizeof(_VLog) is %zu\n", sizeof(_VLog));
}

TEST(VLogTest, dumpTest)
{
  _VLog log;
  log.showDateTime = _VLog::DateTime;
  VMetaDump::dump(&log);
}

TEST(VLogTest, saveLoadTest)
{
  _VLog log;
  log.showDateTime = _VLog::DateTime;
  log.saveToFile("log.json");

  _VLog newLog;
  newLog.loadFromFile("log.json");
  EXPECT_TRUE(newLog.showDateTime == _VLog::DateTime);
}

#endif // GTEST
