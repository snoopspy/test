#ifndef VSTATE_H
#define VSTATE_H

#include <QMetaType>

typedef enum {
	None,
	Closed,
	Opening,
	Opened,
	Closing
} VState;
Q_DECLARE_METATYPE(VState)

/*
class VState
{
	//Q_GADGET

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

	VState(_VState state) { m_state = state; }
	operator _VState() { return m_state; }

private:
	_VState m_state;
};
Q_DECLARE_METATYPE(VState)
*/

#endif // VSTATE_H
