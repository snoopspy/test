#ifndef VMETATYPE_H
#define VMETATYPE_H

#include <QMetaType>

class VMetaType
{
public:
	static void dump(QMetaType& mt);
	static void dumpAll();
};

#endif // VMETATYPE_H
