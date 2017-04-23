#include "qnnwrapper.h"

QNNWrapper::QNNWrapper(QString &dbname,
                       QObject *parent) : QObject(parent),
    conn(NULL)
{
    if(!sqlite3_open(dbname.toStdString().c_str(), &conn)) {
        //
    } else {
        //
    }
}
