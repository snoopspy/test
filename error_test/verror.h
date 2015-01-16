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
		UNKNOWN = 1,
		NOT_CLOSED_STATE
	};

public:
	std::type_info *ti;
	QString msg;
	int code;

public:
	virtual ~VError() {}
	VError(const VError& rhs);
	VError& operator = (const VError& rhs);

public:
	VError()
	{
		ti = (std::type_info*)&typeid(*this);
		msg = "";
		code = OK;
	}

	VError(const QString msg, const int code)
	{
		ti = (std::type_info*)&typeid(*this);
		this->msg = msg;
		this->code = code;
	}

public:
	const char* className();
	void clear();
	void dump();
	void dump(const char* file, const int line, const char* func);
};

#define VERROR_CTOR(ERROR_CLASS_NAME) \
	ERROR_CLASS_NAME() : VError() \
	{ \
		ti = (std::type_info*)&typeid(*this); \
	} \
	ERROR_CLASS_NAME(const QString msg, const int code) : VError(msg, code) \
	{ \
		ti = (std::type_info*)&typeid(*this); \
	}

#define SET_ERROR(ERROR_CLASS_NAME, MSG, CODE) \
	{ \
		error = ERROR_CLASS_NAME(MSG, CODE); \
		error.dump(__FILE__, __LINE__, __func__); \
	}

#endif // VERR_H
