#include "vobject.h"

#include <QByteArray>
#include <QMetaObject>
#include <QMetaProperty>

VObject::VObject(VObject* parent) : QObject(parent)
{

}

VObject::~VObject()
{

}

void VObject::load(VVar& var)
{
    const QMetaObject* mobj = this->metaObject();
    int cnt = mobj->propertyCount();
    for (int i = 0; i < cnt; i++)
    {
        QMetaProperty pro = mobj->property(i);
        const char* name = pro.name();
        QVariant value = var[name];
        this->setProperty(name, value);
    }
}

void VObject::save(VVar& var)
{
    const QMetaObject* mobj = this->metaObject();
    int cnt = mobj->propertyCount();
    for (int i = 0; i < cnt; i++)
    {
        QMetaProperty pro = mobj->property(i);
        const char* name = pro.name();
        QVariant value = this->property(name);
        var[name] = value;
    }
}
