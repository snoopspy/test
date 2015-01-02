#include <QDebug>
#include "vmetaobject.h"

void VMetaObject::dump(QObject* obj)
{
	QString objectName = obj->objectName();
	dump((QMetaObject*)obj->metaObject());
}

void VMetaObject::dump(QMetaObject* mobj)
{
	const char* className = mobj->className();
	int propertyCount = mobj->propertyCount();
	qDebug() << "className" << className << "propertyCount" << propertyCount;
	for (int i = 0; i < propertyCount; i++)
	{
		QMetaProperty mpro = mobj->property(i);
		dump(&mpro);
	}

	int enumeratorCount = mobj->enumeratorCount();
	qDebug() << "className" << className << "enumeratorCount" << enumeratorCount;
	for (int i = 0; i < enumeratorCount; i++)
	{
		QMetaEnum menum = mobj->enumerator(i);
		dump(&menum);
	}
}

void VMetaObject::dump(QMetaProperty *mpro)
{
	const char* name = mpro->name();
	qDebug() << name;
	if (mpro->isEnumType())
	{
		QMetaEnum menum = mpro->enumerator();
		dump(&menum);
	}
}

void VMetaObject::dump(QMetaEnum *menum)
{
	const char* name = menum->name();
	qDebug() << name;
	qDebug() << "  enum type";
	int keyCount = menum->keyCount();
	for (int i = 0; i < keyCount; i++)
	{
		const char* key = menum->key(i);
		qDebug() << "   " << key;
	}
}
