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

#endif // VSTATE_H
