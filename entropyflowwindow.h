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
                               QObject *parent = 0);

    EntropyDiagram get_points();
signals:

public slots:
    //
protected:
    EntropyDiagram points;
    const size_t cWindowSz;
};

#endif // ENTROPYFLOWWINDOW_H
