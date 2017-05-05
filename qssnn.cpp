#include "qssnn.h"

SimScanNN::SimScanNN(tinyxml2::XMLDocument &xml,
                     QObject *parent) : QObject(parent),
    nn(xml)
{
    //
}

SimScanNN::SimScanNN(char *xml_str, QObject *parent) : QObject(parent),
    nn(tinyxml2::XMLDocument().Parse(xml_str))
{}

SimScanNN::SimScanNN(QObject *parent) : QObject(parent),
    nn(new OpenNN::NeuralNetwork())
{
    //
}

QString SimScanNN::toString() {
    tinyxml2::XMLPrinter printer;
    tinyxml2::XMLDocument *doc = nn.to_XML();
    QString result = (doc && doc->Accept(&printer)) ?
                QString(printer.CStr()) : DefaultEmpty();
    delete doc;
    return result;
}

QString SimScanNN::DefaultEmpty() {
    tinyxml2::XMLDocument *doc = OpenNN::NeuralNetwork().to_XML();
    tinyxml2::XMLPrinter printer;
    QString result = (doc && doc->Accept(&printer)) ?
                QString(printer.CStr()) : QString();
    delete doc;
    return result;
}
