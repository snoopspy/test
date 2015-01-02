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

class Foo {
	Q_GADGET
	Q_PROPERTY(Color1 color1 MEMBER color1)
	Q_ENUMS(Color1)
	Q_ENUMS(Color2)
public:
	enum Color1 { Blue1, Red1, Pink1 };
	enum Color2 { Blue2, Red2, Pink2 };
private:
	Color1 color11;
	//Color1 color12;
};

#endif // VSTATE_H
