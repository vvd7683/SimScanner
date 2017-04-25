#ifndef _entropy_h_
#define _entropy_h_

#include <Windows.h>
#include <math.h>
#include <vector>

#define _COUNT(x)		(sizeof(x)/sizeof(*x))

class Entropy
{
private:
	double _value;
	double _calc_entropy(PBYTE pData, ULONG DataSz);
	//static double _log2(double number);
public:
	Entropy(PBYTE pData, ULONG DataSz);
	double value() { return _value; }
	__declspec(property(
		get = value))
		double
		Value;
};

typedef double EntropyPoint;//TODO: make pair
typedef std::vector<EntropyPoint> EntropyDiagram;

#endif
