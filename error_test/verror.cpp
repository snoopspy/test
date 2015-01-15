#include <cxxabi.h>
#include <QDebug>
#include "verror.h"

VError::~VError()
{
}

VError::VError(const VError& rhs)
{
	ti = (std::type_info*)&typeid(rhs);
	msg = rhs.msg;
	code = rhs.code;
}

VError& VError::operator = (const VError& rhs)
{
	if (code == OK)
	{
		ti = (std::type_info*)&typeid(rhs);
		msg = rhs.msg;
		code = rhs.code;
	}
	return *this;
}

VError::VError()
{
	clear();
}

VError::VError(const QString msg, const int code)
{
	ti = (std::type_info*)&typeid(*this);
	this->msg = msg;
	this->code = code;
}

const char* VError::className()
{
	char *res = abi::__cxa_demangle(ti->name(), 0, 0, NULL);
	//char *res = abi::__cxa_demangle(typeid(*this).name(), 0, 0, NULL);
	return res;
}

void VError::clear()
{
	msg = "";
	code = OK;
}

void VError::dump()
{
	qDebug() << "className() return" << className() << msg << code;
}

#ifdef GTEST
#include <gtest/gtest.h>
#include <QDebug>

class VErrTest : public ::testing::Test {};

class Obj {};
class ObjError : public VError
{
public:
	enum {
		OBJ_ERR = 999
	};

public:
	V_ERROR_CTOR(ObjError)
};

TEST_F(VErrTest, commonTest)
{
	VError error;
	error.dump();
}

TEST_F(VErrTest, objTest)
{
	ObjError objError("OBJ_ERR", ObjError::OBJ_ERR);
	objError.dump();
}

TEST_F(VErrTest, typeInfoTest)
{
	VError error;
	error.dump();
	EXPECT_TRUE(error.ti == &typeid(VError));

	ObjError objError;
	objError.dump();
	EXPECT_TRUE(objError.ti == &typeid(ObjError));
}

TEST_F(VErrTest, assignTypeInfoTest)
{
	ObjError objError;
	VError error(objError);
	error.dump();
	EXPECT_TRUE(error.ti == &typeid(ObjError));
}

#endif // GTEST
