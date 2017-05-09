#ifndef QSSNN_H
#define QSSNN_H

/*
 * Neural network basic wrapper class
 */
#include <QObject>
//#include <QMap>
#include <opennn.h>
#include <tinyxml2.h>

#include "macro.h"
#include "ss_types.h"

class SimScanNN : public QObject
{
    Q_OBJECT
public:
    typedef unsigned int PROFILE_ID;
    typedef NNType ssNNType;
    enum ssNNState {
        nnsFailure = -1,
        nnsDisabled = 0,
        nnsTraining,
        nnsActual,

        nnsCount
    };

    unsigned int get_inputs_count() {
        return 0;
    }
    __declspec(property(
        get = get_inputs_count))
    unsigned int inputsCount;

    explicit SimScanNN(tinyxml2::XMLDocument &xml,
                       SimScanNN::ssNNType init_type = SimScanNN::ssNNType::nntUnknown,
                       QObject *parent = 0);
    explicit SimScanNN(const char *xml_str,
                       SimScanNN::ssNNType init_type = SimScanNN::ssNNType::nntUnknown,
                       QObject *parent = 0);
    explicit SimScanNN(SimScanNN::ssNNType init_type = SimScanNN::ssNNType::nntUnknown,
                       QObject *parent = 0);

    QString toString();
    static SimScanNN *fromString(QString &str);

    static QString DefaultEmpty();
    SimScanNN::ssNNState getState() { return nn_state; }

    SimScanNN::ssNNType getNnType() { return nn_type; }
signals:
    void signalSimilarity(double similarity);
public slots:
    //
protected:
    OpenNN::NeuralNetwork nn;
    SimScanNN::ssNNType nn_type;
    SimScanNN::ssNNState nn_state;
};

#endif // QSSNN_H
