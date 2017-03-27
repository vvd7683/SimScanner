#include "entropy.h"

Entropy::Entropy(PBYTE pData, 
	ULONG DataSz) : _value(_calc_entropy(pData, DataSz)) 
{}

double Entropy::_calc_entropy(PBYTE pData, ULONG DataSz) {
	double entropy = 0.;
	if (!DataSz)
		return 0.;
	ULONG statistics[0x100] = { 0 };
	for (ULONG i = 0; i < DataSz; ++i) {
		const int x = pData[i];
		statistics[x]++;
	}

	for (int i = 0; i < _COUNT(statistics); ++i) {
		if(const double c_freq = ((double)statistics[i]) / ((double)DataSz))
			entropy -= c_freq * log2(c_freq);
	}

	return entropy;
}
