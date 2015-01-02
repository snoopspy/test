#ifndef VERR_H
#define VERR_H

#include <QString>

class VErr
{
public:
	enum {
		OK = 0,
		FAIL = -1,
		UNKNOWN = 1
	};

public:
	int code;
	QString msg;

public:
	VErr() { code = OK; msg = ""; }
	virtual ~VErr() {}
	VErr(const VErr& rhs);
	VErr& operator = (const VErr& rhs);
	VErr(const int code, const QString msg) { this->code = code; this->msg = msg; }
};

class VNetErr : public VErr
{
public:
	enum {
		PORT_IS_ZERO = 100
	};

public:
	VNetErr(const int code, const QString msg) { this->code = code; this->msg = msg; }
};

#endif // VERR_H
