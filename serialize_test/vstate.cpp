#include "vstate.h"

#ifdef GTEST
#include <gtest/gtest.h>
#include <QDebug>

class VStateTest : public ::testing::Test
{

};

TEST_F(VStateTest, commonTest)
{
	qDebug() << "sizeof(VState)" << sizeof(VState);
}

TEST_F(VStateTest, saveTest)
{
	VState state  = VState::Opened;
	QVariant variant = state;

	switch (state)
	{
	case VState::None:;
	case VState::Closed:;
	case VState::Opening:;
	case VState::Opened:;
	case VState::Closing:;
	}

	qDebug() << "userType" << variant.userType();
	qDebug() << "type" << variant.type();
	qDebug() << "typeName" << variant.typeName();
}

#endif // GTEST
