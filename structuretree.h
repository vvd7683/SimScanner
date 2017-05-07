#ifndef STRUCTURETREE_H
#define STRUCTURETREE_H

/*
 * Structured Memory reflection of neuroprofiles database
 * containing tuned neural nets, sample descriptors etc
 */
#include <QTreeWidget>
#include <QtCharts/QChart>

#include "entropychartitem.h"
#include "entropychartview.h"

class StructureTree : public QTreeWidget
{
    Q_OBJECT
public:
    StructureTree(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE {
        switch(event->type())
        {
        case QEvent::MouseMove:
        {
            emit signalMouseMove(itemAt(event->x(), event->y()));
            break;
        }
        default:
            break;
        }

        event->accept();
    }
Q_SIGNALS:
    void signalMouseMove(QTreeWidgetItem *item);
};

#endif // STRUCTURETREE_H
