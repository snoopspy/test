// #include <QCoreApplication> // gilgil temp
#include <QDebug>

#include "vcouple.h"
#include "vfile.h"
#include "vip.h"
#include "vperson.h"

void sizeTest()
{
	qDebug() << "sizeof(QString)" << sizeof(QString);
	qDebug() << "sizeof(QObject)" << sizeof(QObject);

	qDebug() << "sizeof(VIp)" << sizeof(VIp);
	qDebug() << "sizeof(VObject)" << sizeof(VObject);
	qDebug() << "sizeof(VVar)" << sizeof(VVar);
	qDebug() << "sizeof(VFile)" << sizeof(VFile);
	qDebug() << "sizeof(VPerson)" << sizeof(VPerson);
	qDebug() << "sizeof(VCouple)" << sizeof(VCouple);
}

void ipTest()
{
	VVar var;
	{
		VIp ip(1234);
		var["ip"] = ip;
	}
	{
		VIp newIp;
		newIp = var["ip"];
		qDebug() << (quint32)newIp;
	}
}

void fileTest()
{
    VVar var;
    {
        VFile file;
        file.setFileName("test.txt");
        var << file;
    }

    {
        VFile newFile;
        var >> newFile;
        qDebug() << "fileName" << newFile.fileName();
    }
}

void personTest()
{
    VVar var;
    {
        VPerson person;
        person.setAge(43);
        person.setName("gilgil");
        var << person;
    }
    {
        VPerson newPerson;
        var >> newPerson;
        qDebug() << "age" << newPerson.age();
        qDebug() << "name" << newPerson.name();
    }
}

void coupleTest()
{
    VVar var;
    {
        VCouple couple;
        couple.man().setAge(43);
        couple.man().setName("gilgil");
        couple.woman().setAge(40);
        couple.woman().setName("marsaj");
        var << couple;
    }
    {
        VCouple newCouple;
        var >> newCouple;
        qDebug() << newCouple.man().age();
        qDebug() << newCouple.man().name();
        qDebug() << newCouple.woman().age();
        qDebug() << newCouple.woman().name();
    }
}

int main(int argc, char *argv[])
{
    // QCoreApplication a(argc, argv); // gilgil temp
    Q_UNUSED(argc)
    Q_UNUSED(argv)

	//sizeTest();
	ipTest();
	//fileTest();
	//personTest();
	//coupleTest();

    return 0;
}
