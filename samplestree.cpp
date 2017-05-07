#include "samplestree.h"

SamplesTree::SamplesTree(QObject *parent) : QObject(parent)
{

}

void SamplesTree::slotGotSample(QString &family_name,
                                unsigned int sample_no, SimScanNN *nn)
{
    QMap<QString,
            QMap<unsigned int,
            SimScanNN *>>::iterator family_iter =
            families.find(family_name);
    if(family_iter == families.end())
        family_iter =
                families.insert(family_name,
                                QMap<unsigned int, SimScanNN *>());
    QMap<unsigned int,
            SimScanNN *>::iterator sample_iter =
            (*family_iter).find(sample_no);
    if(sample_iter == (*family_iter).end())
        sample_iter =
                (*family_iter).insert(sample_no, nn);
    (*sample_iter) = nn;
}
