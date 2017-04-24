#ifndef QDBPROFILE_H
#define QDBPROFILE_H

#include <QObject>
#include <QVector>
#include <tinyxml2.h>

#include "sqlite/sqlite3.h"
#include "qssnn.h"

class DbProfile : public QObject
{
    Q_OBJECT
public:
    typedef SimScanNN::PROFILE_ID PROFILE_ID;
    typedef SimScanNN::ssNNKind nnKind;
    typedef SimScanNN::ssNNType nnType;
    explicit DbProfile(PROFILE_ID ProfileId, QObject *parent = 0);
    explicit DbProfile(QString &Family,
              const int c_index,
              const nnType c_nn_type,
              const nnKind c_nn_kind,
              QObject *parent = 0);
    ~DbProfile() {
        delete ssnn;
    }

    static QVector<DbProfile *> loadProfiles();
    SimScanNN *getNN();
signals:
    void signalDbError(QString msg);
    void signalSimilar(QString &, const int, const nnType, const nnKind, double );
public slots:
    void slotSimilarity(double similarity);
protected:
    PROFILE_ID profile_id;
    SimScanNN *ssnn;
    QString xml_str;
    QString family;
    int idx;
    nnType nn_type;
    nnKind nn_kind;
private:
    double threshold;
    static int loadProfilesCallback(void*,int,char**,char**);
    static int loadProfileCallback(void*,int,char**,char**);
};

#endif // QDBPROFILE_H
