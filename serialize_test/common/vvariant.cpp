#include "vvariant.h"

#include <QDebug>

void VVariant::dump(QVariant v)
{
	qDebug() << "type" << v.type() << (int)v.type();
	qDebug() << "typeName" << v.typeName();
	qDebug() << "data" << v.data();
	char* p = (char*)v.data();
	qDebug() << (int)*p;
}


void VVariant::dumpAll()
{

}
