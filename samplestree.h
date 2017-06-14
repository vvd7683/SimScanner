#ifndef SAMPLESTREE_H
#define SAMPLESTREE_H

#include <QObject>
#include <QVector>
#include <QMap>

class SamplesTree : public QObject
{
    Q_OBJECT
public:
    explicit SamplesTree(QObject *parent = 0);

signals:

public slots:
    void slotGotSample(QString &family_name, unsigned int sample_no);
protected:
};

#endif // SAMPLESTREE_H
