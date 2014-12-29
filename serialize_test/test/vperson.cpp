#include "vperson.h"

VPerson::VPerson(VObject* parent) : VObject(parent)
{
    m_age = 0;
    m_name = "";
}

VPerson::VPerson(const VPerson& rhs) : VObject(0)
{
    m_age = rhs.m_age;
    m_name = rhs.m_name;
}

VPerson& VPerson::operator = (const VPerson& rhs)
{
    m_age = rhs.age();
    m_name = rhs.name();
    return *this;
}

VPerson::~VPerson()
{

}

int VPerson::age() const
{
    return m_age;
}

void VPerson::setAge(int age)
{
    m_age = age;
}

QString VPerson::name() const
{
    return m_name;
}

void VPerson::setName(QString name)
{
    m_name = name;
}
