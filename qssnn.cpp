#include "qssnn.h"

SimScanNN::SimScanNN(const ssNNType c_type,
                     const ssNNKind c_kind,
                     QString &from,
                     QObject *parent) : QObject(parent),
    cType(c_type),
    cKind(c_kind),
    nn(new OpenNN::NeuralNetwork(from.toStdString()))
{
    //
}
