#ifndef QDBPROFILE_H
#define QDBPROFILE_H

#include <QObject>

#include "sqlite/sqlite3.h"

class DbProfile : public QObject
{
    Q_OBJECT
public:
    typedef unsigned int PROFILE_ID;
    explicit DbProfile(PROFILE_ID ProfileId, QObject *parent = 0);
protected:
    PROFILE_ID profile_id;
signals:

public slots:
};

#endif // QDBPROFILE_H
