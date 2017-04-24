#include "qssnn.h"

SimScanNN::SimScanNN(tinyxml2::XMLDocument &xml,
                     QObject *parent) : QObject(parent),
    nn(new OpenNN::NeuralNetwork(xml))
{
    //
}
