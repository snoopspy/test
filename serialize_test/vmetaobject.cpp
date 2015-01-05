#include <QDebug>
#include "vmetaobject.h"

QString duplicate(char ch, int count)
{
	QString res;
	for (int i = 0; i < count; i++)
		res += ch;
	return res;
}

void VMetaObject::dump(QObject* obj, int ident)
{
	QString objectName = obj->objectName();
	dump((QMetaObject*)obj->metaObject(), obj, ident);
}

void VMetaObject::dump(QMetaObject* mobj, QObject* obj, int ident)
{
	const char* className = mobj->className();
	QString objectName = NULL;
	if (obj != NULL)
		objectName = obj->objectName();
	printf("%s%s %s\n", qPrintable(duplicate(' ', ident)), className, qPrintable(objectName));

	int propertyCount = mobj->propertyCount();
	//qDebug() << "className" << className << "propertyCount" << propertyCount; // gilgil temp 2015.01.05
	for (int i = 0; i < propertyCount; i++)
	{
		QMetaProperty mpro = mobj->property(i);
		dump(&mpro, obj, ident + 1);
	}

	/*
	int enumeratorCount = mobj->enumeratorCount();
	qDebug() << "className" << className << "enumeratorCount" << enumeratorCount; // gilgil temp 2015.01.05
	for (int i = 0; i < enumeratorCount; i++)
	{
		QMetaEnum menum = mobj->enumerator(i);
		dump(&menum, obj, ident + 1);
	}
	*/
}

void VMetaObject::dump(QMetaProperty *mpro, QObject* obj, int ident)
{
	const char* name = mpro->name();
	QVariant var = obj->property(name);
	QString value = var.toString();
	if (mpro->isEnumType())
	{
		QMetaEnum menum = mpro->enumerator();
		value = menum.key(var.toInt());
	}

	printf("%s%s %s\n", qPrintable(duplicate(' ', ident)), name, qPrintable(value));
	/*
	if (mpro->isEnumType())
	{
		QMetaEnum menum = mpro->enumerator();
		dump(&menum);
	}
	*/
}

void VMetaObject::dump(QMetaEnum *menum, QObject* obj, int ident)
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
