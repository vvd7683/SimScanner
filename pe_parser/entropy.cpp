#include "entropy.h"

Entropy::Entropy(unsigned char *pData,
    size_t DataSz) : _value(0.), _size(DataSz)
{
    _calc_entropy(pData, DataSz);
}

EntropyType Entropy::_calc_entropy(unsigned char *pData,
                                  size_t DataSz)
{
	/*
	* Основной метод расчёта энтропии
	*/
    ZEROARR(statistics);//Очиска таблицы частот
    _value = 0.;
	if (!DataSz)
		return 0.;//У блока памяти нулевой длины нулевая энтропия
	//Расчёт таблицы частот символов для блока памяти
    for (unsigned long i = 0; i < DataSz; ++i) {
		const int x = pData[i];
		statistics[x]++;
	}
	//Расчёт информационной энтропии по формуле Шеннона
    for (int i = 0; i < COUNT(statistics); ++i) {
		//Если значение в таблице ненулевое...
        if(const EntropyType c_freq = ((EntropyType)statistics[i]) /
                ((EntropyType)DataSz))
				//... добавляем в сумму значение энтропии для i-ого символа ( - pi * log2(pi) )
            _value -= c_freq * log2(c_freq);
	}

    return _value;
}

EntropyType Entropy::append_byte(unsigned char val) {
	/*
	Добавление байта к энтропии уже обсчитанного блока
	*/
    if(const EntropyType c_freq =
            ((EntropyType)statistics[val]) /
            ((EntropyType)_size))
			/*
			Удаляем вклад старого значения в таблице частот ( - pi * log2(pi) ), 
			где i == val, из значения энтропии
			*/
        _value += c_freq * log2(c_freq);
    _size++;//увеличение блока данных на байт
    statistics[val]++;//Увеличение значения в таблице частот
    if(const EntropyType c_freq =
            ((EntropyType)statistics[val]) /
            ((EntropyType)_size))
			//Добавляем вклад нового значения в таблице частот из значения энтропии
        _value -= c_freq * log2(c_freq);
    return _value;
}

EntropyType Entropy::reduce_byte(unsigned char val) {
	/*
	Удаление байта из энтропии уже обсчитанного блока
	*/
    if(const EntropyType c_freq =
            ((EntropyType)statistics[val]) /
            ((EntropyType)_size))
			/*
			Удаляем вклад старого значения в таблице частот ( - pi * log2(pi) ),
			где i == val, из значения энтропии
			*/
			_value += c_freq * log2(c_freq);
    _size--;//уменьшение блока данных на байт
    statistics[val]--;//Уменьшение значения в таблице частот
    if(const EntropyType c_freq =
            ((EntropyType)statistics[val]) /
            ((EntropyType)_size))
			//Добавляем вклад нового значения в таблице частот из значения энтропии
        _value -= c_freq * log2(c_freq);
    return _value;
}




