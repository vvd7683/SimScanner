#include "ss_defs.h"

QMap<NNType, QString> getNnTypes() {
    QMap<NNType, QString> result;
    result.insert(NNType::nntFullFileImage, QString("Full file image"));
    result.insert(NNType::nntAnySection, QString("Any section"));
    result.insert(NNType::nntCodeSection, QString("Code section"));
    result.insert(NNType::nntResource, QString("Resuorce section"));
    result.insert(NNType::nntData, QString("Data section"));
    result.insert(NNType::nntOverlay, QString("Overlay"));
    return result;
}
