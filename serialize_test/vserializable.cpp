#include <QDebug>
#include <QFile>
#include "vserializable.h"

bool VSerializable::loadFromFile(QString fileName, QString path)
{
  VRep src;
  VRep &rep = src;
  if (!rep.loadFromFile(fileName))
  {
    // log // gilgil temp 2015.01.26
    return false;
  }
  QStringList nodes = path.split("/");
  foreach (QString node, nodes)
  {
    if (node == "") continue;
    VRep::iterator it = rep.find(node);
    if (it == rep.end())
    {
      // log // gilgil temp 2015.01.26
      return false;
    }
    rep = it.value().toMap();
  }
  this->load(rep);
  return true;
}

bool VSerializable::saveToFile(const QString fileName, QString path)
{
  VRep root;
  VRep* rep = &root;
  if (QFile::exists(fileName) && !root.loadFromFile(fileName))
  {
    // log // gilgil temp 2015.01.26
    return false;
  }
  QStringList nodes = path.split("/");
  foreach (QString node, nodes)
  {
    if (node == "") continue;
    VRep::iterator it = rep->find(node);
    if (it == rep->end())
    {
      VRep childRep;
      rep->insert(node, childRep);
      it = rep->find(node);
    }
    QVariant& val = it.value();
    rep = (VRep*)(&val);
  }
  this->save(*rep);
  return root.saveToFile(fileName);
}

#ifdef GTEST
#include <gtest/gtest.h>

class Obj : public VSerializable
{
public:
  int i;
  QString s;

  virtual void load(VRep& rep)
  {
    i = rep["i"].toInt();
    s = rep["s"].toString();
  }

  virtual void save(VRep& rep)
  {
    rep["i"] = i;
    rep["s"] = s;
  }
};

TEST(SerializeTest, objTest)
{
  Obj obj;
  obj.i = 999;
  obj.s = "hello";

  VRep rep;
  obj.save(rep);

  Obj obj2;
  obj2.load(rep);
  EXPECT_EQ(obj2.i, 999);
  EXPECT_EQ(obj2.s, "hello");
}

TEST(SerializeTest, saveLoadTest)
{
  Obj obj;
  obj.i = 999;
  obj.s = "hello";

  EXPECT_TRUE(obj.saveToFile("obj.json", "mypath/myobj"));

  Obj obj2;
  EXPECT_TRUE(obj2.loadFromFile("obj.json", "mypath/myobj"));
  EXPECT_EQ(obj2.i, 999);
  EXPECT_EQ(obj2.s, "hello");
}

#endif // GTEST
