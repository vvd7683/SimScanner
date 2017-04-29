#ifndef ENTROPY_PARSER_H
#define ENTROPY_PARSER_H

#include "entropyflowwindow.h"
#include "pe_parser/peParser.h"

class peEntropyParser : public peParser
{
public:
    typedef struct EntropyDiagrams {
        EntropyDiagram entropy_diagram;
        EntropyDiagram entropy_derivative_diagram;
        ExtremumDensityDiagram extremum_density;
    } *PEntropyDiagrams, *HEntropyDiagrams;

    peEntropyParser(HANDLE hFile,
        ULONG FileSz,
        ULONG n_step = 1,
        ULONG n_range = 0x200);
    EntropyDiagram *get_entropy_diagram();
    EntropyDiagram *get_entropy_derivative_diagram();
    ExtremumDensityDiagram *get_extremum_density();
    __declspec(property(
        get = get_entropy_diagram))
    EntropyDiagram *entropyDiagram;
    __declspec(property(
        get = get_entropy_derivative_diagram))
    EntropyDiagram *entropyDerivativeDiagram;
    __declspec(property(
        get = get_extremum_density))
    ExtremumDensityDiagram *extremumDensity;
    EntropyDiagram *get_section_entropy(ULONG index);
    __declspec(property(
        get = get_section_entropy))
    EntropyDiagram *SectionEntropyDiagram[];
    //Getter/setter wraps internal variables for future development
    ULONG _get_step();
    ULONG _set_step(ULONG val);
    __declspec(property(
        get = _get_step,
        put = _set_step))
        ULONG Step;
    ULONG _get_range();
    ULONG _set_range(ULONG val);
    __declspec(property(
        get = _get_range,
        put = _set_range))
        ULONG Range;
private:
    ULONG _step;
    ULONG _range;
    EntropyDiagrams entropy_diagrams;
    QVector<EntropyDiagram>sec_diagrams;

    const ULONG _scan_section_entropies();
    EntropyDiagram _scan_section_entropy(ULONG index);
    EntropyDiagram &_scan_entropy();
};

#endif // ENTROPY_PARSER_H
