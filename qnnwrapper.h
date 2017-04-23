#ifndef QNNWRAPPER_H
#define QNNWRAPPER_H

#include <QObject>
#include <opennn.h>
#include "sqlite/sqlite3.h"

class QNNWrapper : public QObject
{
    Q_OBJECT
public:
    QNNWrapper(QString &dbname, QObject *parent = 0);

signals:

public slots:
    //
protected:
    sqlite3 *conn;
};

#endif // QNNWRAPPER_H
