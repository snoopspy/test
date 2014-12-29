#ifndef VPERSON_H
#define VPERSON_H

#include "vobject.h"

class VPerson : public VObject
{
    Q_OBJECT
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    VPerson(VObject* parent = 0);
    VPerson(const VPerson& rhs);
    VPerson& operator = (const VPerson& rhs);
    virtual ~VPerson();

public:
    int age() const;
    void setAge(int age);

    QString name() const;
    void setName(QString name);

signals:
    void ageChanged(int age);
    void nameChanged(QString name);

private:
    int m_age;
    QString m_name;
};
Q_DECLARE_METATYPE(VPerson)

#endif // VPERSON_H
