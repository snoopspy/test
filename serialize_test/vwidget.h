#ifndef VWIDGET_H
#define VWIDGET_H

#ifdef QT_GUI_LIB

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

typedef QWidget     VWidget;
typedef QTreeWidget VWidgetObject;

class VWidgetItem : public QTreeWidgetItem
{
public:
	explicit VWidgetItem(QVariant* variant, VWidgetObject *wobj) : QTreeWidgetItem(wobj)
	{
		this->variant = variant;
	}
	QVariant* variant;
};

#endif // QT_GUI_LIB

#endif // VWIDGET_H
