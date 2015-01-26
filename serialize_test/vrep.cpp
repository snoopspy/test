#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "vrep.h"

bool VRep::loadFromFile(QString fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly))
    return false;

  QByteArray ba = file.readAll();
  file.close();

  QJsonDocument jdoc = QJsonDocument::fromJson(ba);

  QJsonObject jobj = jdoc.object();

  *this = jobj.toVariantMap();

  return true;
}

bool VRep::saveToFile(QString fileName)
{
  QJsonObject jobj = QJsonObject::fromVariantMap(*this);

  QJsonDocument jdoc;
  jdoc.setObject(jobj);

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly))
    return false;

  file.write(jdoc.toJson());
  file.close();

  return true;
}
