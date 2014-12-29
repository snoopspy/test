#ifndef VVARIANT_H
#define VVARIANT_H

#include <QDebug>
#include <QVariant>

class VVariant
{
public:
	static void dump(QVariant v);
	static void dumpAll();
};

#endif // VVARIANT_H
