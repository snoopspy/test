#ifndef VLOG_H
#define VLOG_H

#include "vmetaobject.h"
#include "vobject.h"

class VLog : public VObject
{
	Q_OBJECT
	Q_PROPERTY(VShowDateTime showDateTime MEMBER showDateTime)
	Q_ENUMS(VShowDateTime)

public:
	enum VShowDateTime
	{
		None,
		Time,
		DateTime
	} showDateTime;

public:
	explicit VLog(VObject *parent = 0) : VObject(parent) {}
};
//Q_DECLARE_METATYPE(VLog::VShowDateTime)

#endif // VLOG_H
