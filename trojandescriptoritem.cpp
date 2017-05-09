#include "trojandescriptoritem.h"

TrojanDescriptorItem::TrojanDescriptorItem(const QVector<SimScanNN *> &nns,
                                           const SimScanNN::ssNNState c_state,
                                           QTreeWidgetItem *parent) : QTreeWidgetItem(parent),
    state(c_state),
    nn_profiles(new QTreeWidgetItem(this)),
    negative(Q_NULLPTR),
    positive(Q_NULLPTR),
    control(Q_NULLPTR)
{
    nn_profiles->setText(0, QString("Neuroprofiles"));
    foreach (SimScanNN *nn, nns) {
        new NNItem(*nn, nn_profiles);
    }
    if(state == SimScanNN::nnsTraining) {
        //TODO: append training sample items
    }
}

bool TrojanDescriptorItem::train() {
    QVector<NNItem *>nn_items_to_train;
    if(state == SimScanNN::nnsTraining) {
        nn_items_to_train = get_nn_to_train();
    }
    return false;
}

QVector<NNItem *> TrojanDescriptorItem::get_nn_to_train() {
    QVector<NNItem *>result;
    for(int i = 0; i < nn_profiles->childCount(); ++i) {
        if(NNItem *nn_item =
                dynamic_cast<NNItem *>(child(i)))
        {
            switch(nn_item->getState())
            {
            case SimScanNN::ssNNState::nnsTraining:
                result.push_back(nn_item);
                break;
            default:
                break;
            }
        }
    }
    return result;
}
