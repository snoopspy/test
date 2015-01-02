#include <cxxabi.h>
#include <QDebug>
#include "verror.h"

VError::VError()
{
	ti = &typeid(VError);
	msg = "";
	code = OK;
}

VError::VError(const VError& rhs)
{
	ti = rhs.ti;
	msg = rhs.msg;
	code = rhs.code;
}

VError& VError::operator = (const VError& rhs)
{
	ti = rhs.ti;
	msg = rhs.msg;
	code = rhs.code;
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
	qDebug() <<file << line << func << className() << msg << code;
}

#ifdef GTEST
#include <gtest/gtest.h>
#include <typeinfo>
#include <QDebug>

class VErrTest : public ::testing::Test
{
};

TEST_F(VErrTest, commonTest)
{
	VError error;
	error.dump();
}

class Obj {};
class ObjError : public VErr<Obj>
{
public:
	enum {
		OBJ_ERROR888 = 888,
		OBJ_ERROR999 = 999
	};

public:
	V_ERROR_CTOR(ObjError, Obj)
};

TEST_F(VErrTest, ObjTest)
{
	ObjError objError("888 error", ObjError::OBJ_ERROR888);
	//dump(&objError);
}

TEST_F(VErrTest, AssignTest)
{
	VError error;

	error = ObjError("999 error", ObjError::OBJ_ERROR999);
	error.dump();

	error = ObjError("999 error", ObjError::OBJ_ERROR999, __FILE__, __LINE__, __func__);
	//error.dump();

	error = V_ERROR(ObjError, "999 error", ObjError::OBJ_ERROR999);
	error.dump();
}

#endif // GTEST
