#ifndef ENTROPYFLOWWINDOW_H
#define ENTROPYFLOWWINDOW_H

#include <QObject>
#include <QVector>

#include "pe_parser/entropy.h"

class EntropyFlowWindow : public QObject
{
    Q_OBJECT
public:
    explicit EntropyFlowWindow(unsigned char *Area,
                               size_t AreaSz,
                               size_t WindowSz = 0x400,
                               size_t StepSz = 1,
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
