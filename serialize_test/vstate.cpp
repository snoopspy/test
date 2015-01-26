#include "vstate.h"

#ifdef GTEST
#include <gtest/gtest.h>
#include <QDebug>
#include "vmetadump.h"

TEST(VStateTest, sizeTest)
{
  printf("sizeof(VState)=%zu\n", sizeof(VState));
  EXPECT_TRUE(sizeof(VState) == sizeof(int));
}

TEST(VStateTest, varTest)
{
  VState state = Opened;
  QVariant var = QVariant::fromValue<VState>(state);
  VMetaDump::dump(&var);

  int userType = var.userType();
  EXPECT_TRUE(userType == qMetaTypeId<VState>());

  QVariant::Type type = var.type();
  EXPECT_TRUE((int)type == QMetaType::User);

  QString typeName = var.typeName();
  EXPECT_TRUE(typeName == "VState");
}

#endif // GTEST
