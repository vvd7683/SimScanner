#ifndef QDBPROFILE_H
#define QDBPROFILE_H

#include <QObject>

class QDbProfile : public QObject
{
    Q_OBJECT
public:
    explicit QDbProfile(QObject *parent = 0);

signals:

public slots:
};

#endif // QDBPROFILE_H