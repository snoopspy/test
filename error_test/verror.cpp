#include <cxxabi.h>
#include <QDebug>
#include "verror.h"

VError::VError()
{
	ti = &typeid(VError);
	msg = "";
	code = 0;
}

VError::VError(const VError& rhs)
{
	ti = rhs.ti;
	msg = rhs.msg;
	code = rhs.code;
}

VError& VError::operator = (const VError& rhs)
{
	if (code == 0)
	{
		ti = rhs.ti;
		msg = rhs.msg;
		code = rhs.code;
	}
	return *this;
}

const char* VError::className()
{
	char *res = abi::__cxa_demangle(ti->name(), 0, 0, NULL);
	return res;
}

void VError::dump()
{
	qDebug() << className() << msg << code;
}

void VError::dump(const char* file, const int line, const char* func)
{
	qDebug() << file << line << func << className() << msg << code;
}

#ifdef GTEST
#include <gtest/gtest.h>
#include <typeinfo>
#include <QDebug>

class VErrTest : public ::testing::Test {};

class Obj {};
class ObjError : public VError
{
public:
	enum {
		OBJ_ERROR_1 = 1,
		OBJ_ERROR_2 = 2
	};

public:
	V_ERROR_CTOR(ObjError)
};

TEST_F(VErrTest, commonTest)
{
	VError error;
	error.dump();
}

TEST_F(VErrTest, ObjTest)
{
	ObjError objErr("OBJ_ERROR_1", ObjError::OBJ_ERROR_1);
	//dump(&objError);
}

TEST_F(VErrTest, AssignTest)
{
	VError error;

	error = ObjError("2 argument", ObjError::OBJ_ERROR_2);
	error.dump();

	error = ObjError("5 argument", ObjError::OBJ_ERROR_2, __FILE__, __LINE__, __func__);
	//error.dump();

	error = V_ERROR(ObjError, "V_ERROR", ObjError::OBJ_ERROR_2);
	error.dump();
}

#endif // GTEST
