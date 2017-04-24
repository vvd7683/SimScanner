#include "dbprofile.h"

const char *cDefaultDbName = "profiles.vdb";

const char *SqlInitNeuroprofiles =
        "CREATE TABLE IF NOT EXISTS neuroprofiles (id INTEGER PRIMARY KEY, family TEXT, idx INTEEGER, nn_type INTEGER, nn_kind INTEGER, profile TEXT, threshold DOUBLE, learned BOOLEAN, created TEXT NOT NULL DEFAULT (NOW()), comment TEXT, UNIQUE(family, idx, nn_type, nn_kind));";
const char *SqlLoadNeuroprofiles = "SELECT id FROM neuroprofiles;";
const char *SqlLoadNeuroprofile = "SELECT nn_type, nn_kind, profile, threshold, learned, created FROM neuroprofiles WHERE id=%d;";
const char *SqlNewNeuroprofile = "INSERT INTO neuroprofiles (family, idx, nn_type, nn_kind, profile, threshold, learned) VALUES (%s, %d, %d, %d, %s, %f, %d);";
const char *SqlGetNeuroprofileId = "SELECT id FROM neuroprofiles WHERE family='%s' AND idx=%d AND nn_type=%d AND nn_kind=%d;";
const char *SqlGetFamilies = "SELECT DISTINCT family FROM neuroprofiles;";
const char *SqlGetFamily = "SELECT DISTINCT idx FROM neuroprofiles WHERE family='%s';";

const char *cIdCol = "id";
const char *cFamilyCol = "family";
const char *cIdxCol = "idx";
const char *cNnTypeCol = "nn_type";
const char *cNnKindCol = "nn_kind";
const char *cProfileCol = "profile";
const char *cThresholdCol = "threshold";
const char *cLearnedCol = "learned";

DbProfile::DbProfile(PROFILE_ID ProfileId,
                       QObject *parent) : QObject(parent),
    nn_type(nnType::nntUnknown),
    nn_kind(nnKind::nnkUnknown),
    idx(0),
    profile_id(ProfileId),
    ssnn(NULL),
    threshold(.0),
    b_learned(false)
{
    sqlite3 *db = NULL;
    if(!sqlite3_open(cDefaultDbName, &db)) {
        //TODO: load profile with UID=ProfileId
        sqlite3_close(db);
    } else {
        //
    }
}

DbProfile::DbProfile(QString &Family,
                     const int c_index,
                     const nnType c_nn_type,
                     const nnKind c_nn_kind,
                     const double cThreshold,
                     const bool cLearned,
                     QObject *parent) : QObject(parent),
    family(Family),
    idx(c_index),
    nn_type(c_nn_type),
    nn_kind(c_nn_kind),
    profile_id(0),
    ssnn(NULL),
    threshold(cThreshold),
    b_learned(cLearned)
{
    sqlite3 *db = NULL;
    if(!sqlite3_open(cDefaultDbName, &db))
    {
        char *err = NULL;
        if(!sqlite3_exec(
                    db,
                    QString().sprintf(
                        SqlNewNeuroprofile,
                        Family.toStdString(//family - %s
                            ).c_str(
                            ),
                        c_index,//idx - %d
                        (int)c_nn_type,//nn_type - %d
                        (int)c_nn_kind,//nn_kind - %d
                        SimScanNN::Empty(//profile - %s
                            ).toStdString(
                            ).c_str(
                            ),
                        threshold,//threshold - %f
                        (int)b_learned//learned - %d
                        ).toStdString(
                        ).c_str(
                        ),
                    NULL,
                    NULL,
                    &err
                    )
                )
        {
            if(!sqlite3_exec(
                        db,
                        QString(
                            ).sprintf(
                            SqlGetNeuroprofileId,
                            Family.toStdString(
                                ).c_str(
                                ),
                            c_index,
                            (int)c_nn_type,
                            (int)c_nn_kind
                            ).toStdString(
                            ).c_str(
                            ),
                        loadProfileCallback,//callback
                        this,//param
                        &err
                        )
                    )
            {
                //
            } else {
                throw;
            }
        } else {
            throw;
        }
        sqlite3_close(db);
    } else {
        throw;
    }
}

int DbProfile::getIdCallback(void *data, int argc, char **argv, char **azColName) {
    DbProfile *This = (DbProfile *)data;
    if((argc == 1) && (!strcmp(*azColName, cIdCol))) {
        if(const unsigned int cId = QString(*argv).toInt()) {
            if(!This->profile_id)
                This->profile_id = cId;
            else {
                //TODO: compare IDs
            }
        }
    }
    return 0;
}

int DbProfile::loadProfileCallback(void *data, int argc, char **argv, char **azColName) {
    DbProfile *This = (DbProfile *)data;
    for(int i = 0; i < argc; ++i) {
        if(!strcmp(azColName[i], cIdCol)) {
            if(This->profile_id) {
                //TODO: compare
            } else {
                This->profile_id = QString(argv[i]).toInt();
            }
            continue;
        }
        if(!strcmp(azColName[i], cNnTypeCol)) {
            if(This->nn_type == nnType::nntUnknown) {
                This->nn_type = (nnType)QString(argv[i]).toInt();
            } else {
                //TODO: compare
            }
            continue;
        }
        if(!strcmp(azColName[i], cNnKindCol)) {
            if(This->nn_kind == nnKind::nnkUnknown) {
                This->nn_kind = (nnKind)QString(argv[i]).toInt();
            } else {
                //TODO: compare
            }
            continue;
        }
        if(!strcmp(azColName[i], cFamilyCol)) {
            if(This->family.length()) {
                //TODO: compare
            } else {
                This->family = QString(argv[i]);
            }
            continue;
        }
        if(!strcmp(azColName[i], cIdxCol)) {
            if(This->idx) {
                //TODO: compare
            } else {
                This->idx = QString(argv[i]).toInt();
            }
            continue;
        }
        if(!strcmp(azColName[i], cProfileCol)) {
            This->xml_str = QString(argv[i]);
            continue;
        }
        if(!strcmp(azColName[i], cThresholdCol)) {
            This->threshold = QString(argv[i]).toDouble();
            continue;
        }
        if(!strcmp(azColName[i], cLearnedCol)) {
            This->b_learned = !!QString(argv[i]).toInt();
            continue;
        }
    }
    return 0;
}

int DbProfile::loadProfilesCallback(void *data, int argc, char **argv, char **azColName) {
    QVector<DbProfile *> &result = *(QVector<DbProfile *> *)data;
    if((argc == 1) && (!strcmp(*azColName, cIdCol))) {
        if(const unsigned int cId = QString(*argv).toInt()) {
            result.push_back(new DbProfile(cId));
        }
    }
    return 0;
}

QVector<DbProfile *> DbProfile::loadProfiles() {
    QVector<DbProfile *> result;
    sqlite3 *db = NULL;
    if(!sqlite3_open(cDefaultDbName, &db))
    {
        char *err = NULL;
        if(!sqlite3_exec(db, SqlInitNeuroprofiles, NULL, NULL, &err)) {
            if(!sqlite3_exec(db, SqlLoadNeuroprofiles, loadProfilesCallback, &result, &err)) {
                //
            } else {
                throw;
            }
        } else {
            throw;
        }
        sqlite3_close(db);
    } else {
        //
    }
    return result;
}

QVector<QString> DbProfile::getFamilies() {
    QVector<QString> result;
    sqlite3 *db = NULL;
    if(!sqlite3_open(cDefaultDbName, &db))
    {
        char *err = NULL;
        if(!sqlite3_exec(db,
                         SqlGetFamilies,
                         NULL/* TODO: make callback */,
                         &result,
                         &err))
        {
            //
        } else {
            throw;
        }
        sqlite3_close(db);
    } else {
        //
    }
    return result;
}

QVector<int> DbProfile::getFamilyIndexes(QString Family) {
    QVector<int> result;
    sqlite3 *db = NULL;
    if(!sqlite3_open(cDefaultDbName, &db))
    {
        char *err = NULL;
        if(!sqlite3_exec(db,
                         QString(
                             ).sprintf(
                             SqlGetFamily,
                             Family.toStdString(
                                 ).c_str(
                                 )
                             ).toStdString(
                             ).c_str(
                             ),
                         NULL/* TODO: make callback */,
                         &result,
                         &err))
        {
            //
        } else {
            throw;
        }
        sqlite3_close(db);
    } else {
        //
    }
    return result;
}

SimScanNN *DbProfile::getNN() {
    if(!ssnn) {
        tinyxml2::XMLDocument xml;
        if(xml.Parse(xml_str.toStdString().c_str())) {
            ssnn = new SimScanNN(xml);
            connect(ssnn, &SimScanNN::signalSimilarity, this, &DbProfile::slotSimilarity);
        }
    }
    return ssnn;
}

void DbProfile::slotSimilarity(double similarity) {
    if(fabs(similarity - 1.) < threshold) {
        //Is similar
        emit signalSimilar(family, idx, nn_type, nn_kind, similarity);
    }
}
