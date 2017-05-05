#ifndef ENTROPYNN_H
#define ENTROPYNN_H

#include <QVector>

#include "qssnn.h"
#include "pe_parser/entropy.h"

const size_t cDefaultPoints = 0x20;

class EntropyFixedNN : public SimScanNN
{
public:
    EntropyFixedNN(EntropyDiagram &diagram,
                   const size_t cWindowSz = cDefaultWindowSz);
protected:
    const size_t c_window_sz;
};

class EntropyRelativeNN : public SimScanNN
{
public:
    EntropyRelativeNN(EntropyDiagram &diagram,
                   const size_t cPoints = cDefaultRelativePoints) : SimScanNN()
    {
        const size_t cDiagramLength = diagram.length();
        const size_t cWindowSz = cDiagramLength / cPoints;
        QVector<EntropyY> pts;
        pts.push_back((EntropyY)cDiagramLength);//First is a length.
        for(size_t n = 0; n < cDiagramLength; n += cWindowSz) {
            pts.push_back(diagram[n].entropy_value);
        }
    }
protected:
    const size_t c_window_sz;
};

#endif // ENTROPYNN_H
