#ifndef VSTATE_H
#define VSTATE_H

#include <QMetaType>

typedef enum {
	None,
	Closed,
	Opening,
	Opened,
	Closing
} _VState;
Q_DECLARE_METATYPE(_VState)

#endif // VSTATE_H
