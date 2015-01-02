#include "verr.h"

VErr::VErr(const VErr& rhs)
{
	void* _this = (void*)this;
	void* _rhs = (void*)&rhs;
	memcpy(_this, _rhs, sizeof(void*));
	//void** __this = &_this;
	//void** __rhs = &_rhs;
	//*__this = *__rhs;
	code = rhs.code;
	msg = rhs.msg;
}

VErr& VErr::operator = (const VErr& rhs)
{
	void* _this = (void*)this;
	void* _rhs = (void*)&rhs;
	memcpy(_this, _rhs, sizeof(void*));
	code = rhs.code;
	msg = rhs.msg;
	return *this;
}

#ifdef GTEST
#include <gtest/gtest.h>
#include <typeinfo>
#include <QDebug>

void dump(VErr* err)
{
	//if (dynamic_cast<VErr*>(err)) qDebug() << "VErr";
	//if (dynamic_cast<VNetErr*>(err)) qDebug() << "VNetErr";
	qDebug() << typeid(*err).name();
}

class VErrTest : public ::testing::Test
{
};

TEST_F(VErrTest, commonTest)
{
	VErr err;
	ASSERT_TRUE(err.code == VErr::OK);
	ASSERT_TRUE(err.msg == "");
}

TEST_F(VErrTest, netTest)
{
	VErr err;
	VNetErr netErr(VNetErr::PORT_IS_ZERO, "port is zero");
	VErr* pErr = &err;

	dump(&err);
	dump(&netErr);
	dump(pErr);

	err = netErr;

	dump(&err);
	dump(&err);
	dump(&netErr);
	dump(pErr);
}

#endif // GTEST


