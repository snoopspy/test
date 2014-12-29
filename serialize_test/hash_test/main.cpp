#include <QCoreApplication>
#include <QDebug>
#include <QVariant>

#include "../common/vip.h"

typedef QVariantHash VVar;
// typedef QVariant VVar;

class Person
{
public:
    int age;
    QString name;

    virtual void load(VVar& var)
    {
        age = var["age"].toInt();
        name = var["name"].toString();
    }

    virtual void save(VVar& var)
    {
        var["age"] = age;
        var["name"] = name;
    }
};

class Couple
{
public:
    Person man;
    Person woman;

    virtual void load(VVar& var)
    {
        VVar varMan = var["man"].toHash();
        man.load(varMan);
        VVar varWoman = var["woman"].toHash();
        woman.load(varWoman);
    }

    virtual void save(VVar& var)
    {
        VVar varMan;
        man.save(varMan);
        var.insert("man", varMan);
        VVar varWoman;
        woman.save(varWoman);
        var.insert("woman", varWoman);
    }
};

void testPerson()
{
    VVar var;

    {
        Person person;
        person.age = 40;
        person.name = "gilgil";
        person.save(var);
    }

    {
        Person person2;
        person2.load(var);
        qDebug() << person2.age;
        qDebug() << person2.name;
    }
}

void testCouple()
{
    VVar var;

    {
        Couple couple;
        couple.man.age = 43;
        couple.man.name = "gilgil";
        couple.woman.age = 40;
        couple.woman.name = "marsaj";
        couple.save(var);
    }

    {
        Couple couple2;
        couple2.load(var);
        qDebug() << couple2.man.age;
        qDebug() << couple2.man.name;
        qDebug() << couple2.woman.age;
        qDebug() << couple2.woman.name;
    }
}

void testIp()
{
    VVar var;

    {
        VIp ip(1234);
        QVariant varIp;
        varIp.setValue(ip);
        var.insert("ip", varIp);
    }

    {
        VIp ip;
        QVariant varIp = var["ip"];
        ip = varIp.value<VIp>();
        qDebug() << ip.m_ip;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //testPerson();
    //testCouple();
    testIp();

    return 0;
}
