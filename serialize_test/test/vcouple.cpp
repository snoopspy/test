#include "vcouple.h"

VCouple::VCouple(VObject* parent) : VObject(parent)
{

}

VCouple::~VCouple()
{

}

VPerson& VCouple::man()
{
    return m_man;
}

void VCouple::setMan(VPerson& man)
{
    m_man = man;
}

VPerson& VCouple::woman()
{
    return m_woman;
}

void VCouple::setWoman(VPerson& woman)
{
    m_woman = woman;
}
