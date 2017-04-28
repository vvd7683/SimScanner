#ifndef ENTROPY_PARSER_H
#define ENTROPY_PARSER_H

#include "entropyflowwindow.h"
#include "pe_parser/peParser.h"

class peEntropyParser : public peParser
{
public:
    peEntropyParser(HANDLE hFile,
        ULONG FileSz,
        ULONG n_step = 1,
        ULONG n_range = 0x200) : peParser(hFile,
        FileSz),
        _step(n_step),
        _range(n_range)
    {}
    EntropyDiagram *get_entropy() {
        return &entropy_diagram;
    }
    __declspec(property(
        get = get_entropy))
    EntropyDiagram *entropyDiagram;
    EntropyDiagram *get_section_entropy(ULONG index);
    __declspec(property(
        get = get_section_entropy))
    EntropyDiagram *SectionEntropyDiagram[];
    //Getter/setter wraps internal variables for future development
    ULONG _get_step() { return _step; }
    ULONG _set_step(ULONG val) { return _step = val; }
    __declspec(property(
        get = _get_step,
        put = _set_step))
        ULONG Step;
    ULONG _get_range() { return _range; }
    ULONG _set_range(ULONG val) { return _range = val; }
    __declspec(property(
        get = _get_range,
        put = _set_range))
        ULONG Range;
private:
    ULONG _step;
    ULONG _range;
    EntropyDiagram entropy_diagram;
    QVector<EntropyDiagram>sec_diagrams;

    const ULONG _scan_section_entropies();
    EntropyDiagram _scan_section_entropy(ULONG index);
    EntropyDiagram &_scan_entropy();
};

#endif // ENTROPY_PARSER_H
