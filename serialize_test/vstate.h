#ifndef VSTATE_H
#define VSTATE_H

#include "vmetaobject.h"

class VState
{
	Q_GADGET
public:
	enum _VState {
		None,
		Closed,
		Opening,
		Opened,
		Closing
	};
public:
	VState() {}
	V_QVAR_CONVERSION(VState)
	V_TYPE_CONVERSION(VState, _VState , m_state)

private:
	_VState m_state;
};
Q_DECLARE_METATYPE(VState)

#endif // VSTATE_H
