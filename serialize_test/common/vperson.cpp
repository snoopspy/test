#include <QDebug>

#include "vperson.h"

VPerson::VPerson() : QObject(0)
{
	qDebug() << "VPerson::VPerson()";
	m_age = 0;
}

VPerson::VPerson(int age) : QObject(0)
{
	qDebug() << "VPerson::VPerson(age)" << age;
	m_age = age;
}

VPerson::VPerson(const VPerson& rhs) : QObject(0)
{
	m_age = rhs.m_age;
}

VPerson::~VPerson()
{
	qDebug() << "VPerson::~VPerson()";
}

int VPerson::age() const
{
	qDebug() << "VPerson::age()";
	return m_age;
}

void VPerson::setAge(int age)
{
	qDebug() << "VPerson::setAge()" << age;
	m_age = age;
}
