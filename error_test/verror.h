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
	std::type_info *ti;
	QString msg;
	int code;

public:
	virtual ~VError();
	VError(const VError& rhs);
	VError& operator = (const VError& rhs);

public:
	VError();
	VError(const QString msg, const int code);
	VError(const QString msg, const int code, const char* file, const int line, const char* func);

public:
	const char* className();
	void clear();
	void dump();
	void dump(const char* file, const int line, const char* func);
};

#define V_ERROR_CTOR(ERROR_CLASS_NAME) \
	ERROR_CLASS_NAME() : VError() {} \
	ERROR_CLASS_NAME(const QString msg, const int code) : VError(msg, code) {} \
	ERROR_CLASS_NAME(const QString msg, const int code, const char* file, const int line, const char* func) : VError(msg, code, file, line, func) {}

#define V_ERROR(ERROR_CLASS_NAME, MSG, CODE) \
	ERROR_CLASS_NAME(MSG, CODE, __FILE__, __LINE__, __FUNCTION__)

#endif // VERR_H
