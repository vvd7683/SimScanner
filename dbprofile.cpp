#include "dbprofile.h"

const char *cDefaultDbName = "profiles.vdb";
//TODO: set threshold double field
const char *SqlInitNeuroprofiles =
        "CREATE TABLE IF NOT EXISTS neuroprofiles (id INTEGER PRIMARY KEY, family TEXT, idx INTEEGER, nn_type INTEGER, nn_kind INTEGER, profile TEXT, created TEXT NOT NULL DEFAULT (NOW()), comment TEXT, UNIQUE(family, idx, nn_type, nn_kind));";
const char *SqlLoadNeuroprofiles = "SELECT id FROM neuroprofiles;";
const char *SqlLoadNeuroprofile = "SELECT nn_type, nn_kind, profile, created FROM neuroprofiles WHERE id=%d;";
const char *SqlNewNeuroprofile = "INSERT INTO neuroprofiles (family, idx, nn_type, nn_kind, profile) VALUES (%s, %d, %d, %d, %s);";
const char *SqlGetNeuroprofile = "SELECT id FROM neuroprofiles WHERE family=%s AND idx=%d AND nn_type=%d AND nn_kind=%d;";

DbProfile::DbProfile(PROFILE_ID ProfileId,
                       QObject *parent) : QObject(parent),
    nn_type(nnType::nntUnknown),
    nn_kind(nnKind::nnkUnknown),
    idx(0),
    profile_id(ProfileId),
    ssnn(NULL),
    threshold(.0)
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
                     QObject *parent) : QObject(parent),
    family(Family),
    idx(c_index),
    nn_type(c_nn_type),
    nn_kind(c_nn_kind),
    profile_id(0),
    ssnn(NULL),
    threshold(.0)
{
    sqlite3 *db = NULL;
    if(!sqlite3_open(cDefaultDbName, &db))
    {
        char *err = NULL;
        if(!sqlite3_exec(
                    db,
                    QString().sprintf(
                        SqlNewNeuroprofile,
                        Family.toStdString(
                            ).c_str(
                            ),
                        c_index,
                        (int)c_nn_type,
                        (int)c_nn_kind,
                        SimScanNN::Empty(
                            ).toStdString(
                            ).c_str(
                            )
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
                            SqlGetNeuroprofile,
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

int DbProfile::loadProfileCallback(void *data, int argc, char **argv, char **azColName) {
    DbProfile *This = (DbProfile *)data;
    for(int i = 0; i < argc; ++i) {
        if(!strcmp(azColName[i], "id")) {
            if(This->profile_id) {
                //TODO: compare
            } else {
                This->profile_id = QString(argv[i]).toInt();
            }
            continue;
        }
        if(!strcmp(azColName[i], "nn_type")) {
            if(This->nn_type == nnType::nntUnknown) {
                This->nn_type = (nnType)QString(argv[i]).toInt();
            } else {
                //TODO: compare
            }
            continue;
        }
        if(!strcmp(azColName[i], "nn_kind")) {
            if(This->nn_kind == nnKind::nnkUnknown) {
                This->nn_kind = (nnKind)QString(argv[i]).toInt();
            } else {
                //TODO: compare
            }
            continue;
        }
        if(!strcmp(azColName[i], "family")) {
            if(This->family.length()) {
                //TODO: compare
            } else {
                This->family = QString(argv[i]);
            }
        }
        if(!strcmp(azColName[i], "idx")) {
            if(This->idx) {
                //TODO: compare
            } else {
                This->idx = QString(argv[i]).toInt();
            }
        }
        if(!strcmp(azColName[i], "profile")) {
            This->xml_str = QString(argv[i]);
        }
    }
    return 0;
}

int DbProfile::loadProfilesCallback(void *data, int argc, char **argv, char **azColName) {
    QVector<DbProfile *> &result = *(QVector<DbProfile *> *)data;
    if((argc == 1) && (!strcmp(*azColName, "id"))) {
        if(const unsigned int cId = atoi(argv[0])) {
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
