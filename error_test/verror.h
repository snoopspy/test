#ifndef VERR_H
#define VERR_H

#include <typeinfo>
#include <QString>

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
	QString msg;
	int code;

public:
	VError();
	VError(const VError& rhs);
	VError& operator = (const VError& rhs);
	const char* className();
	void dump();
};

template <class T>
class VErr : public VError
{
public:
	VErr()
	{
		ti = &typeid(VErr<T>);
		msg = "";
		code = OK;
	}

	VErr(const QString msg, const int code)
	{
		ti = (std::type_info*)&typeid(VErr<T>);
		this->msg = msg;
		this->code = code;
	}
};

#define V_ERROR_CTOR(ERROR_CLASS_NAME, CLASS_NAME) \
ERROR_CLASS_NAME() : VErr<CLASS_NAME>() {} \
ERROR_CLASS_NAME(const QString msg, const int code) : VErr<CLASS_NAME>(msg, code) {}

#endif // VERR_H
