#ifndef VLOG_H
#define VLOG_H

#include "vmetadump.h"
#include "vobject.h"

class _VLog : public _VObject
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
  _VLog(_VObject *parent = 0) : _VObject(parent) { showDateTime = None; }

public:
	Q_PROPERTY(VShowDateTime showDateTime MEMBER showDateTime)
	Q_ENUMS(VShowDateTime)
};
//Q_DECLARE_METATYPE(_VLog::VShowDateTime)

#endif // VLOG_H
