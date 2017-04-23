#ifndef QSSNN_H
#define QSSNN_H

#include <QObject>
#include <opennn.h>

#include "macro.h"

class SimScanNN : public QObject
{
    Q_OBJECT
public:
    typedef unsigned int PROFILE_ID;
    enum class ssNNType {
        nntFullFileImage = 0,
        nntAnySection,
        nntCodeSection,
        nntResource,
        nntData,
        nntOverlay,

        nntCount
    };

    enum class ssNNKind {
        nnkFixed = 0,
        nnkExtremum,
        nnkRelative,
        //derivative curves
        nnkDerivedFixed,
        nnkDerivedExtremum,
        nnkDerivedRelative,

        nnkCount
    };

    SimScanNN(const ssNNType c_type,
              const ssNNKind c_kind,
              QString &from,
              QObject *parent = 0);

    static QString Empty() {
        return QString();
    }

    const ssNNType cType;
    const ssNNKind cKind;
signals:

public slots:
    //
private:
    OpenNN::NeuralNetwork nn;
};

#endif // QSSNN_H
