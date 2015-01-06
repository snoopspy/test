#ifndef VSTRREP_H
#define VSTRREP_H

#include <QMetaObject>
#include "vrep.h"

class VStrRep
{
public:
	static VRep toStrRep(const VRep& rep, const QMetaObject* mobj);
	static VRep toRep(const VRep& strRep, const QMetaObject* mobj);
};

#endif // VSTRREP_H
