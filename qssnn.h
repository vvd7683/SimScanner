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
        nntUnknown = -1,
        nntFullFileImage = 0,
        nntAnySection,
        nntCodeSection,
        nntResource,
        nntData,
        nntOverlay,

        nntCount
    };

    enum class ssNNKind {
        nnkUnknown = -1,
        nnkFixed = 0,
        nnkExtremum,
        nnkRelative,
        //derivative curves
        nnkDerivedFixed,
        nnkDerivedExtremum,
        nnkDerivedRelative,

        nnkCount
    };

    explicit SimScanNN(tinyxml2::XMLDocument &xml,
              QObject *parent = 0);
    explicit SimScanNN(char *xml_str,
              QObject *parent = 0);
    explicit SimScanNN(QObject *parent = 0);

    QString toString();
    static SimScanNN *fromString(QString &str) {
        tinyxml2::XMLDocument xml;
        if(!!xml.Parse(
            str.toStdString(
                ).c_str(
                )
            )) throw;

        return new SimScanNN(xml);
    }

    static QString DefaultEmpty();
signals:
    void signalSimilarity(double similarity);
public slots:
    //
private:
    OpenNN::NeuralNetwork nn;
};

#endif // QSSNN_H
