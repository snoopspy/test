#include <QDebug>
#include "vserializable.h"

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
  EXPECT_TRUE(obj2.i == 999);
  EXPECT_TRUE(obj2.s == "hello");
}

#endif // GTEST
