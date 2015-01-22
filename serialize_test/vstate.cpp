#include "vstate.h"

#ifdef GTEST
#include <gtest/gtest.h>
#include <QDebug>
#include "vmetadump.h"

TEST(VStateTest, sizeTest)
{
  printf("sizeof(_VState)=%zu\n", sizeof(_VState));
	EXPECT_TRUE(sizeof(_VState) == sizeof(int));
}

TEST(VStateTest, varTest)
{
	_VState state = Opened;
	QVariant var = QVariant::fromValue<_VState>(state);
	VMetaDump::dump(&var);

	int userType = var.userType();
	EXPECT_TRUE(userType == qMetaTypeId<_VState>());

	QVariant::Type type = var.type();
	EXPECT_TRUE((int)type == QMetaType::User);

	QString typeName = var.typeName();
  EXPECT_TRUE(typeName == "_VState");
}

#endif // GTEST
