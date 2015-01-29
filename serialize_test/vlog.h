#ifndef VLOG_H
#define VLOG_H

#include "vmetadump.h"
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
  VLog(VObject *parent = 0) : VObject(parent) { showDateTime = None; }
};
//Q_DECLARE_METATYPE(_VLog::VShowDateTime)

#endif // VLOG_H
