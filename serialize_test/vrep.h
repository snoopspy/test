#ifndef VREP_H
#define VREP_H

#include <QVariantMap>

class VRep : public QVariantMap
{
public:
  VRep() {}
  VRep(const QVariantMap& rhs) { *((QVariantMap*)this) = rhs; }

public:
  bool loadFromFile(QString fileName);
  bool saveToFile(QString fileName);
};

#endif // VREP_H
