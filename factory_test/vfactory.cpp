#include "vfactory.h"

VFactory::VFactory()
{
  createMap.clear();
  hierachyMap.clear();
  categoryMap.clear();
}

VFactory::~VFactory()
{
  createMap.clear();
  hierachyMap.clear();
  categoryMap.clear();
}

void VFactory::registerObject(const QMetaObject* mobj)
{
  while (mobj != NULL)
  {
    QString className = QString(mobj->className());
    createMap[className] = mobj;

    const QMetaObject* parentMObj = mobj->superClass();
    VMetaObjectList& mobjList = hierachyMap[parentMObj];
    if (mobjList.indexOf(mobj) == -1)
      mobjList.push_back(mobj);

    mobj = parentMObj;
  }
}

void VFactory::registerCategory(QString categoryName, const QMetaObject* mobj)
{
  VMetaObjectList& mobjList = categoryMap[categoryName];
  if (mobjList.indexOf(mobj) == -1)
    mobjList.push_back(mobj);
}

VFactory::VMetaObjectList VFactory::getChildsByParentClassName(QString parentClassName)
{
  for (VHierachyMap::iterator it = hierachyMap.begin(); it != hierachyMap.end(); it++)
  {
    const QMetaObject* mobj = it.key();
    if (mobj == NULL) continue;
    if (QString(mobj->className()) == parentClassName)
    {
      VMetaObjectList& mobjList = it.value();
      return mobjList;
    }
  }
  return VMetaObjectList();
}

VFactory::VMetaObjectList VFactory::getChildsByAncestorClassName(QString ancestorClassName)
{
  VMetaObjectList res;
  for (VHierachyMap::iterator it = hierachyMap.begin(); it != hierachyMap.end(); it++)
  {
    const QMetaObject* mobj = it.key();
    if (mobj == NULL) continue;
    if (isAncestor(mobj, ancestorClassName))
    {
      VMetaObjectList& mobjList = it.value();
      res += mobjList;
    }
  }
  return res;
}

VFactory::VMetaObjectList VFactory::getChildsByCategoryName(QString categoryName)
{
  for (VCategoryMap::iterator it = categoryMap.begin(); it != categoryMap.end(); it++)
  {
    QString _categoryName = it.key();
    if (_categoryName == categoryName)
    {
      VMetaObjectList& mobjList = it.value();
      return mobjList;
    }
  }
  return VMetaObjectList();
}

QObject* VFactory::createByClassName(QString className)
{
  VCreateMap::iterator it = createMap.find(className);
  if (it == createMap.end())
    return NULL;
  const QMetaObject* mobj = it.value();
  if (mobj == NULL)
    return NULL;
  QObject* obj = mobj->newInstance();
  if (obj == NULL)
    return NULL;
  return obj;
}

bool VFactory::isAncestor(const QMetaObject* mobj, QString className)
{
  while (mobj != NULL)
  {
    if (QString(mobj->className()) == className)
      return true;
    mobj = mobj->superClass();
  }
  return false;
}

VFactory& VFactory::instance()
{
  static VFactory factory;
  return factory;
}

#ifdef GTEST
#include "vfactorytest.h"

class VFactoryTest : public testing::Test
{
protected:
  VFactory factory;
  virtual void SetUp()
  {
    Obj1 obj1;
    factory.registerObject(obj1.metaObject());
    Obj2 obj2;
    factory.registerObject(obj2.metaObject());
    Obj3 obj3;
    factory.registerObject(obj3.metaObject());

    Obj31 obj31;
    factory.registerObject(obj31.metaObject());
    Obj32 obj32;
    factory.registerObject(obj32.metaObject());
    Obj33 obj33;
    factory.registerObject(obj33.metaObject());
    Obj34 obj34;
    factory.registerObject(obj34.metaObject());

    factory.registerCategory("MyObj", obj1.metaObject());
    factory.registerCategory("MyObj", obj2.metaObject());
    factory.registerCategory("MyObj", obj3.metaObject());
  }

  virtual void TearDown()
  {

  }
};

TEST_F(VFactoryTest, createObjectTest)
{
  QObject* object;

  object = factory.createByClassName("Obj");
  EXPECT_TRUE(dynamic_cast<Obj*>(object) != NULL);
  delete object;

  object = factory.createByClassName("Obj1");
  EXPECT_TRUE(dynamic_cast<Obj1*>(object) != NULL);
  delete object;

  object = factory.createByClassName("Obj2");
  EXPECT_TRUE(dynamic_cast<Obj2*>(object) != NULL);
  delete object;

  object = factory.createByClassName("Obj3");
  EXPECT_TRUE(dynamic_cast<Obj3*>(object) != NULL);
  delete object;

  object = factory.createByClassName("Obj31");
  EXPECT_TRUE(dynamic_cast<Obj31*>(object) != NULL);
  delete object;

  object = factory.createByClassName("Obj32");
  EXPECT_TRUE(dynamic_cast<Obj32*>(object) != NULL);
  delete object;

  object = factory.createByClassName("Obj33");
  EXPECT_TRUE(dynamic_cast<Obj33*>(object) != NULL);
  delete object;

  object = factory.createByClassName("Obj34");
  EXPECT_TRUE(dynamic_cast<Obj34*>(object) != NULL);
  delete object;
}

TEST_F(VFactoryTest, parentClassNameTest)
{
  {
    VFactory::VMetaObjectList mobjList = factory.getChildsByParentClassName("Obj");
    foreach (const QMetaObject* mobj, mobjList)
    {
      printf("%s ", mobj->className());
    }
    printf("\n");
    EXPECT_EQ(mobjList.size(), 3); // Obj1, Obj2, Obj3
  }
  {
    VFactory::VMetaObjectList mobjList = factory.getChildsByParentClassName("Obj3");
    foreach (const QMetaObject* mobj, mobjList)
    {
      printf("%s ", mobj->className());
    }
    printf("\n");
    EXPECT_EQ(mobjList.size(), 4); // Obj31, Obj32, Obj33, Obj34
  }
}

TEST_F(VFactoryTest, ancestorClassNameTest)
{
  {
    VFactory::VMetaObjectList mobjList = factory.getChildsByAncestorClassName("Obj");
    foreach (const QMetaObject* mobj, mobjList)
    {
      printf("%s ", mobj->className());
    }
    printf("\n");
    EXPECT_EQ(mobjList.size(), 7); // Obj1, Obj2, Obj3, Obj31, Obj32, Obj33, Obj34
  }
  {
    VFactory::VMetaObjectList mobjList = factory.getChildsByParentClassName("Obj3");
    foreach (const QMetaObject* mobj, mobjList)
    {
      printf("%s ", mobj->className());
    }
    printf("\n");
    EXPECT_EQ(mobjList.size(), 4); // Obj31, Obj32, Obj33, Obj34
  }
}

#endif // GTEST
