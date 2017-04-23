#ifndef QSSNN_H
#define QSSNN_H

#include <QObject>
#include <opennn.h>

class SimScanNN : public QObject
{
    Q_OBJECT
public:
    explicit SimScanNN(QObject *parent = 0);
    enum ssNNType {
        ssnnFullFileImage = 0,
        ssnnAnySection,
        ssnnCodeSection,
        ssnnResource,
        ssnnData,
        ssnnOverlay,

        nnCount
    };

    const ssNNType get_nn_type() {
        return nn_type;
    }

    __declspec( property( get=get_nn_type ) ) const ssNNType cType;
signals:

public slots:
    //
private:
    ssNNType nn_type;
    OpenNN::NeuralNetwork nn;
};

#endif // QSSNN_H
