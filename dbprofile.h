#ifndef QDBPROFILE_H
#define QDBPROFILE_H

#include <QObject>
#include <QVector>

#include "sqlite/sqlite3.h"
#include "qssnn.h"

class DbProfile : public QObject
{
    Q_OBJECT
public:
    typedef SimScanNN::PROFILE_ID PROFILE_ID;
    typedef SimScanNN::ssNNKind nnKind;
    typedef SimScanNN::ssNNType nnType;
    DbProfile(PROFILE_ID ProfileId, QObject *parent = 0);
    DbProfile(QString &Family,
              const int c_index,
              const nnType nn_type,
              const nnKind nn_kind,
              QObject *parent = 0);
    static QVector<DbProfile *> loadProfiles();
signals:
    void signalDbError(QString msg);
public slots:
    //
protected:
    PROFILE_ID profile_id;
private:
    static int loadProfilesCallback(void*,int,char**,char**);
};

#endif // QDBPROFILE_H
