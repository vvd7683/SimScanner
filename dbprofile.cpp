#include "dbprofile.h"

const char *cDefaultDbName = "profiles.vdb";

const char *SqlInitNeuroprofiles =
        "CREATE TABLE IF NOT EXISTS neuroprofiles (id INTEGER PRIMARY KEY, family TEXT, idx INTEEGER, nn_type INTEGER, nn_kind INTEGER, profile TEXT, created TEXT NOT NULL DEFAULT (NOW()), comment TEXT, UNIQUE(family, idx, nn_type, nn_kind));";
const char *SqlLoadNeuroprofiles = "SELECT id FROM neuroprofiles;";
const char *SqlLoadNeuroprofile = "SELECT nn_type, nn_kind, profile, created FROM neuroprofiles WHERE id=%d;";
const char *SqlNewNeuroprofile = "INSERT INTO neuroprofiles (family, idx, nn_type, nn_kind, profile) VALUES (%s, %d, %d, %d, %s);";
const char *SqlGetNeuroprofile = "SELECT id FROM neuroprofiles WHERE family=%s AND idx=%d AND nn_type=%d AND nn_kind=%d;";

DbProfile::DbProfile(PROFILE_ID ProfileId,
                       QObject *parent) : QObject(parent),
    profile_id(ProfileId)
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
                     const nnType nn_type,
                     const nnKind nn_kind,
                     QObject *parent) : QObject(parent)
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
                        (int)nn_type,
                        (int)nn_kind,
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
                            (int)nn_type,
                            (int)nn_kind
                            ).toStdString(
                            ).c_str(
                            ),
                        NULL,//callback
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
