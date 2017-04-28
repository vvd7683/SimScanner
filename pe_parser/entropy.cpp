#include "entropy.h"

Entropy::Entropy(unsigned char *pData,
    size_t DataSz) : _value(0.), _size(DataSz)
{
    _calc_entropy(pData, DataSz);
}

EntropyType Entropy::_calc_entropy(unsigned char *pData,
                                  size_t DataSz)
{
    ZEROARR(statistics);
    _value = 0.;
	if (!DataSz)
		return 0.;
    for (unsigned long i = 0; i < DataSz; ++i) {
		const int x = pData[i];
		statistics[x]++;
	}

    for (int i = 0; i < COUNT(statistics); ++i) {
        if(const EntropyType c_freq = ((EntropyType)statistics[i]) /
                ((EntropyType)DataSz))
            _value -= c_freq * log2(c_freq);
	}

    return _value;
}

EntropyType Entropy::append_byte(unsigned char val) {
    if(const EntropyType c_freq =
            ((EntropyType)statistics[val]) /
            ((EntropyType)_size))
        _value += c_freq * log2(c_freq);
    _size++;
    statistics[val]++;
    if(const EntropyType c_freq =
            ((EntropyType)statistics[val]) /
            ((EntropyType)_size))
        _value -= c_freq * log2(c_freq);
    return _value;
}

EntropyType Entropy::reduce_byte(unsigned char val) {
    if(const EntropyType c_freq =
            ((EntropyType)statistics[val]) /
            ((EntropyType)_size))
        _value += c_freq * log2(c_freq);
    _size--;
    statistics[val]--;
    if(const EntropyType c_freq =
            ((EntropyType)statistics[val]) /
            ((EntropyType)_size))
        _value -= c_freq * log2(c_freq);
    return _value;
}
