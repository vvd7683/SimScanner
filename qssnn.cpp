#include "qssnn.h"

SimScanNN::SimScanNN(tinyxml2::XMLDocument &xml,
                     QObject *parent) : QObject(parent),
    nn(new OpenNN::NeuralNetwork(xml))
{
    //
}

QString SimScanNN::Empty() {
    //QDir::tempPath().append(QDir::separator()).append(tr("temp"));
    return QString();
}
