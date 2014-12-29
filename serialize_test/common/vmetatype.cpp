#include "vmetatype.h"

#include <QDebug>

void VMetaType::dump(QMetaType& mt)
{
	Q_UNUSED(mt)
	qDebug() << "VMetaType::dumpMetaType";
}

void VMetaType::dumpAll()
{
	qDebug() << "VMetaType::dumpAll";
}
