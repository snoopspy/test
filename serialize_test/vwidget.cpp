#include "vwidget.h"

VTreeWidget::VTreeWidget(QWidget *parent, VObject* object) : QTreeWidget(parent)
{
	this->object = object;
}

void VTreeWidget::editingFinished()
{
	QLineEdit* lineEdit = (QLineEdit*)this->sender();
	qDebug() << lineEdit->text();
}

void VTreeWidget::textChanged(const QString &s)
{
	qDebug() << s;
}
