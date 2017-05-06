#ifndef QDBPROFILE_H
#define QDBPROFILE_H

#include <QObject>
#include <QVector>
#include <tinyxml2.h>

#include "sqlite/sqlite3.h"
#include "entropynn.h"

class DbProfile : public QObject
{
    Q_OBJECT
public:
    enum class nnKind {
        nnkUnknown = -1,
        //
        nnkFixed = 0,
        nnkDerivedFixed,
        nnkExtremumFixed,
        //
        nnkRelative,
        nnkExtremumRelative,
        nnkDerivedRelative,

        nnkCount
    };
    typedef SimScanNN::PROFILE_ID PROFILE_ID;
    typedef SimScanNN::ssNNType nnType;
    explicit DbProfile(PROFILE_ID ProfileId, QObject *parent = 0);
    explicit DbProfile(QString &Family,
                       const int c_index,
                       const nnType c_nn_type,
                       const nnKind c_nn_kind,
                       const double cThreashold = .0,
                       const bool cLearned = false,
                       QObject *parent = 0);
    ~DbProfile();

    static QVector<DbProfile *> loadProfiles();
    static QVector<QString> getFamilies();
    static QVector<int> getFamilyIndexes(QString Family);
    SimScanNN *getNN();
    SimScanNN *setNN(SimScanNN *_nn);
signals:
    void signalDbError(QString msg);
    void signalSimilar(QString &, const int, const nnType, const nnKind, double );
public slots:
    void slotSimilarity(double similarity);
protected:
    PROFILE_ID profile_id;
    SimScanNN *ssnn;
    QString xml_serialized;
    QString family;
    int idx;
    nnType nn_type;
    nnKind nn_kind;
private:
    double threshold;
    bool b_learned;
    static int loadProfilesCallback(void*,int,char**,char**);
    static int loadProfileCallback(void*,int,char**,char**);
    static int getIdCallback(void*,int,char**,char**);
};

#endif // QDBPROFILE_H
