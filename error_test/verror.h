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
	void dump(const char* file, const int line, const char* func);
};

#define V_ERROR_CTOR(ERROR_CLASS_NAME) \
	ERROR_CLASS_NAME() \
	{ \
		ti = &typeid(ERROR_CLASS_NAME); \
		msg = ""; \
		code = OK; \
	} \
	ERROR_CLASS_NAME(const QString msg, const int code) \
	{ \
		ti = &typeid(ERROR_CLASS_NAME); \
		this->msg = msg; \
		this->code = code; \
	} \
	ERROR_CLASS_NAME(const QString msg, const int code, const char* file, const int line, const char* func) \
	{ \
		ti = &typeid(ERROR_CLASS_NAME); \
		this->msg = msg; \
		this->code = code; \
		dump(file, line, func); \
	}

#define V_ERROR(ERROR_CLASS_NAME, MSG, CODE) \
	ERROR_CLASS_NAME(MSG, CODE, __FILE__, __LINE__, __FUNCTION__)

#endif // VERR_H
