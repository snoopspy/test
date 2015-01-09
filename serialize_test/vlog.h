#ifndef VLOG_H
#define VLOG_H

#include "vmetadump.h"
#include "vobject.h"

class VLog : public VObject
{
	Q_OBJECT

public:
	enum VShowDateTime
	{
		None,
		Time,
		DateTime
	} showDateTime;

public:
	VLog(VObject *parent = 0) : VObject(parent) { showDateTime = None; }

public:
	Q_PROPERTY(VShowDateTime showDateTime MEMBER showDateTime)
	Q_ENUMS(VShowDateTime)
};
//Q_DECLARE_METATYPE(VLog::VShowDateTime)

#endif // VLOG_H
