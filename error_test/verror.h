#ifndef VERR_H
#define VERR_H

#include <typeinfo>
#include <QString>
#include <cxxabi.h>

class VError
{
public:
	enum {
		OK = 0,
		FAIL = -1,
		UNKNOWN = 1
	};
public:
	const std::type_info* ti;
	int code;
	QString msg;

public:
	VError()
	{
		ti = &typeid(VError);
		code = OK;
		msg = "";
	}

	VError(const VError& rhs)
	{
		ti = rhs.ti;
		code = rhs.code;
		msg = rhs.msg;
	}

	VError& operator = (const VError& rhs)
	{
		ti = rhs.ti;
		code = rhs.code;
		msg = rhs.msg;
		return *this;
	}

	const char* className()
	{
		//int status;
		//char *res = abi::__cxa_demangle(ti->name(), 0, 0, &status);
		char *res = abi::__cxa_demangle(ti->name(), 0, 0, NULL);
		return res;
	}
};

template <class T>
class VErr : public VError
{
public:
	VErr()
	{
		ti = &typeid(VErr<T>);
		code = OK;
		msg = "";
	}

	VErr(const int code, const QString msg)
	{
		ti = (std::type_info*)&typeid(VErr<T>);
		this->code = code;
		this->msg = msg;
	}
};

#define V_ERROR_CTOR(ERROR_CLASS_NAME, CLASS_NAME) \
ERROR_CLASS_NAME() : VErr<CLASS_NAME>() {} \
ERROR_CLASS_NAME(const int code, const QString msg) : VErr<CLASS_NAME>(code, msg) {}

#endif // VERR_H
