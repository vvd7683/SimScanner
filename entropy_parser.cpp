#include "entropy_parser.h"

EntropyDiagram &peEntropyParser::_scan_entropy() {
    if(!entropy_diagram.size()) {
        EntropyFlowWindow efwin(pFileImage,
                          FileImageSz);
        entropy_diagram = efwin.get_points();
        entropy_derivative = efwin.get_derivative();
    }
    return entropy_diagram;
}

EntropyDiagram peEntropyParser::_scan_section_entropy(ULONG index) {
    if (index < SectionsCount) {
        if (Section[index].SizeOfRawData && Section[index].PointerToRawData) {
            const PBYTE c_start = &pFileImage[Section[index].PointerToRawData];
            const size_t c_sz = Section[index].SizeOfRawData;
            return EntropyFlowWindow(c_start, c_sz).get_points();
        }
    } else {
        throw;
    }
    return EntropyDiagram();
}

const ULONG peEntropyParser::_scan_section_entropies() {
    if(!sec_diagrams.size()) {
        sec_diagrams.resize(SectionsCount);
        for(ULONG i = 0; i < SectionsCount; ++i) {
            sec_diagrams[i] = _scan_section_entropy(i);
        }
    }
    return sec_diagrams.size();
}

peEntropyParser::peEntropyParser(HANDLE hFile, ULONG FileSz, ULONG n_step, ULONG n_range) : peParser(hFile,
                                                                                                     FileSz),
    _step(n_step),
    _range(n_range)
{
    //
}

EntropyDiagram *peEntropyParser::get_entropy() {
    _scan_entropy();
    return &entropy_diagram;
}

EntropyDiagram *peEntropyParser::get_derivative() {
    _scan_entropy();
    return &entropy_derivative;
}

EntropyDiagram *peEntropyParser::get_section_entropy(ULONG index) {
    const ULONG c_count =
            _scan_section_entropies();
    if(c_count == SectionsCount &&
            index < c_count)
        return &sec_diagrams[index];
    return Q_NULLPTR;
}

ULONG peEntropyParser::_get_step() { return _step; }

ULONG peEntropyParser::_set_step(ULONG val) { return _step = val; }

ULONG peEntropyParser::_get_range() { return _range; }

ULONG peEntropyParser::_set_range(ULONG val) { return _range = val; }

//-----------------------------------------------------------------------------
