#ifndef VOBJECT_H
#define VOBJECT_H

#include <QObject>

#include "vserializable.h"

class VObject : public QObject, public VSerializable
{
    Q_OBJECT

public:
    explicit VObject(VObject* parent = 0);
    virtual ~VObject();

public:
    virtual void load(VVar& var);
    virtual void save(VVar& var);

signals:

public slots:
};

#endif // VOBJECT_H
