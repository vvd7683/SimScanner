#include "entropynn.h"

EntropyFixedNN::EntropyFixedNN(EntropyDiagram &diagram,
                               const size_t cWindowSz) : SimScanNN(),
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
        pts[n] = diagram[n].entropy_value;
    }
}
