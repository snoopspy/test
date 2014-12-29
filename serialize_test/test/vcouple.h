#ifndef VCOUPLE_H
#define VCOUPLE_H

#include "vperson.h"

class VCouple : public VObject
{
    Q_OBJECT
    Q_PROPERTY(VPerson man READ man WRITE setMan)
    Q_PROPERTY(VPerson woman READ woman WRITE setWoman)

public:
    VCouple(VObject* parent = 0);
    ~VCouple();

public:
    VPerson& man();
    void setMan(VPerson& man);

    VPerson& woman();
    void setWoman(VPerson& woman);

private:
    VPerson m_man;
    VPerson m_woman;
};

#endif // VCOUPLE_H
