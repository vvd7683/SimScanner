#include "qdbprofile.h"

const char *cDefaultDbName = "profiles.vdb";

QDbProfile::QDbProfile(PROFILE_ID ProfileId,
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
