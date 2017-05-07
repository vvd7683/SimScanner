#ifndef QPEFILEMENU_H
#define QPEFILEMENU_H

/*
 * Class of menu including actions associated with PE format
 */
#include <QMenu>
#include <QFileInfo>

#include "qpefile.h"

class QPeFileMenu : public QMenu
{
    Q_OBJECT
public:
    QPeFileMenu(QWidget *parent = Q_NULLPTR);
    QFileInfo *get_info() { return info; }
    QFileInfo *set_info(QFileInfo *_info) {
        if(info) delete info;
        return info = _info ? new QFileInfo(*_info) : Q_NULLPTR;
    }
    //Q_PROPERTY(QFileInfo *PeFileInfo READ get_info WRITE set_info)
    __declspec( property( get=get_info, put=set_info) ) QFileInfo *PeFileInfo;

protected:
    QFileInfo *info;
};

#endif // QPEFILEMENU_H
