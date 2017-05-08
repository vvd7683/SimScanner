#ifndef SS_TYPES_H
#define SS_TYPES_H

enum SsMode {
    ssmFailure = -1,
    ssmScan = 0,
    ssmEdit,

    ssmCount
};

enum class NNType {
    nntUnknown = -1,
    nntFullFileImage = 0,
    nntAnySection,
    nntCodeSection,
    nntResource,
    nntData,
    nntOverlay,

    nntCount
};

#endif // SSMODE_H
