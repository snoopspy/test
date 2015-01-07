#include <QDebug>
#include "vserializable.h"

// ----- gilgil temp 2015.01.07 -----
/*
bool VSerializable::loadFromFile(QString fileName, const QMetaObject* mobj)
{
	VRep strRep;
	if (!strRep.loadFromFile(fileName))
	{
		return false;
	}

	VRep rep;
	if (mobj == NULL)
	{
		rep = strRep;
	} else
	{
		rep = VStrRep::strReptoRep(strRep, mobj);
	}
	this->load(rep);
	return true;
}

bool VSerializable::saveToFile(QString fileName, const QMetaObject* mobj)
{
	VRep rep;
	this->save(rep);
	VRep strRep;
	if (mobj == NULL)
	{
		strRep = rep;
	} else
	{
		strRep = VStrRep::repToStrRep(rep, mobj);
	}
	return strRep.saveToFile(fileName);
}
*/
// ----------------------------------

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
