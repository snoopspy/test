#include "verror.h"

#ifdef GTEST
#include <gtest/gtest.h>
#include <typeinfo>
#include <QDebug>

void dump(VError* error)
{
	//qDebug() << abi::__cxa_demangle(typeid(*error).name(), 0, 0, NULL);
	qDebug() << error->className();
	qDebug() << error->code;
	qDebug() << error->msg;
}

class Obj;
//typedef VError<Obj> VObjError;

class VErrTest : public ::testing::Test
{
};

TEST_F(VErrTest, commonTest)
{
	VError error;
	dump(&error);
}

class Obj {};
class ObjError : public VErr<Obj>
{
public:
	ObjError() : VErr<Obj>() {}
	ObjError(const int code, const QString msg) : VErr<Obj>(code, msg) {}
};

class Obj2;
class Obj2Error : public VErr<Obj2>
{
public:
	V_ERROR_CTOR(Obj2Error, Obj2)
};

TEST_F(VErrTest, ObjTest)
{
	ObjError objError(1, "puhahaha");
	dump(&objError);
}

TEST_F(VErrTest, AssignTest)
{
	VError error;

	error = ObjError(999, "this is obj error");
	dump(&error);
}

#endif // GTEST
