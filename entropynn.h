#ifndef ENTROPYNN_H
#define ENTROPYNN_H

#include <QVector>

#include <opennn.h>
#include <tinyxml2.h>

#include "qssnn.h"
#include "pe_parser/entropy.h"

const size_t cDefaultPoints = 0x20;

template<EntropyY EntropyPoint::* MemPtr>
class FixedNN : public SimScanNN
{
public:
    explicit FixedNN(QString &xmlString,
                     const SimScanNN::ssNNType c_nn_type = SimScanNN::ssNNType::nntUnknown,
                     const size_t cWindowSz = cDefaultWindowSz,
                     QObject *parent = 0) : SimScanNN(xmlString.toStdString().c_str(),
                                                      c_nn_type,
                                                      parent),
        c_window_sz(cWindowSz)
    {
        //
    }
    explicit FixedNN(EntropyDiagram &diagram,
                            const SimScanNN::ssNNType c_nn_type = SimScanNN::ssNNType::nntUnknown,
                            const size_t cWindowSz = cDefaultWindowSz,
                            QObject *parent = 0) : SimScanNN(c_nn_type, parent),
        c_window_sz(cWindowSz)
    {
        const size_t cDiagramLength = diagram.length();
        if(cDiagramLength < cDefaultWindowSz) {
            throw;
        }
        const int cInputsCount = cDiagramLength / cWindowSz;
        QVector<EntropyY> pts;
        pts.resize(cInputsCount);
        for(size_t n = 0; n < cDiagramLength; n += cWindowSz) {
            EntropyPoint &pt = diagram[n];
            pts[n] = pt.*MemPtr;
        }
    }
protected:
    const size_t c_window_sz;
};

typedef class FixedNN<&EntropyPoint::entropy_value> EntropyFixedNN;
typedef class FixedNN<&EntropyPoint::entropy_derivative_value> DerivedFixedNN;
typedef class FixedNN<&EntropyPoint::maximums_density> ExtremumFixedNN;

template<EntropyY EntropyPoint::* MemPtr>
class RelativeNN : public SimScanNN
{
public:
    explicit RelativeNN(QString &xmlString,
                        const SimScanNN::ssNNType c_nn_type = SimScanNN::ssNNType::nntUnknown,
                        const size_t cWindowSz = cDefaultWindowSz,
                        QObject *parent = 0) : SimScanNN(xmlString.toStdString().c_str(),
                                                         c_nn_type,
                                                         parent),
        c_window_sz(cWindowSz)
    {
        //
    }
    explicit RelativeNN(EntropyDiagram &diagram,
                            const SimScanNN::ssNNType c_nn_type = SimScanNN::ssNNType::nntUnknown,
                            const size_t cWindowSz = cDefaultWindowSz,
                            QObject *parent = 0) : SimScanNN(c_nn_type,
                                                             parent),
        c_window_sz(cWindowSz)
    {
        const size_t cDiagramLength = diagram.length();
        if(cDiagramLength < cDefaultWindowSz) {
            throw;
        }
        const int cInputsCount = cDiagramLength / cWindowSz;
        QVector<EntropyY> pts;
        pts.push_back((EntropyY)cDiagramLength);//First is a length.
        for(size_t n = 0; n < cDiagramLength; n += cWindowSz) {
            EntropyPoint &pt = diagram[n];
            pts[n] = pt.*MemPtr;
        }
    }
protected:
    const size_t c_window_sz;
};
typedef class RelativeNN<&EntropyPoint::entropy_value> EntropyRelativeNN;
typedef class RelativeNN<&EntropyPoint::entropy_derivative_value> DerivedRelativeNN;
typedef class RelativeNN<&EntropyPoint::maximums_density> ExtremumRelativeNN;

#endif // ENTROPYNN_H
