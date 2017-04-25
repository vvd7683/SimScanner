#ifndef ENTROPYFLOWWINDOW_H
#define ENTROPYFLOWWINDOW_H

#include <QObject>
#include <QVector>

#include "pe_parser/entropy.h"

class EntropyFlowWindow : public QObject
{
    Q_OBJECT
public:
    explicit EntropyFlowWindow(PBYTE Area,
                               int AreaSz,
                               int WindowSz = 0x400,
                               int StepSz = 1,
                               QObject *parent = 0);

signals:

public slots:
    //
protected:
    QVector<EntropyPoint>points;
    int step;
    int windowSz;
};

#endif // ENTROPYFLOWWINDOW_H
