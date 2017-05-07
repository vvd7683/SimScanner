#ifndef SAMPLESTREE_H
#define SAMPLESTREE_H

#include <QObject>
#include <QVector>
#include <QMap>

#include "entropynn.h"

class SamplesTree : public QObject
{
    Q_OBJECT
public:
    explicit SamplesTree(QObject *parent = 0);

signals:

public slots:
    void slotGotSample(QString &family_name, unsigned int sample_no, SimScanNN *nn);
protected:
    QVector<SimScanNN *>nns;
    QMap<QString, QMap<unsigned int, SimScanNN *>> families;
};

#endif // SAMPLESTREE_H
