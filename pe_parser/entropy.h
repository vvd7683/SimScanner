#ifndef _entropy_h_
#define _entropy_h_

#include <math.h>
#ifdef QT_CORE_LIB
#include <QVector>
#else
#include <Windows.h>
#include <vector>
#endif

#include "macro.h"

const size_t cDefaultWindowSz = 0x400;

typedef double EntropyType;//Определение типа, которым описывается значение энтропии (может быть float - так быстрее)

class Entropy
{
private:
    EntropyType _value;
    size_t _size;//В этом поле сохраняется размер блока, для которого рассчитывается энтропия
    EntropyType _calc_entropy(unsigned char *pData, size_t DataSz);//Основной метод расчёта
	size_t statistics[0x100]; /*
							  Таблица частот символов. 
							  Сумма всех элементов массива 
							  равна длине блока памяти, 
							  для которого рассчитывалась энтропия
							  */
public:
	/*
	Конструктор. На вход принимается указатель и размер блока данных, 
	для которого будет рассчитана энтропия
	*/
    Entropy(unsigned char *pData, size_t DataSz);
	/*
	Объявление константного свойства, 
	обеспечивающего read-only доступ к значению энтропии
	*/
    const EntropyType value() { return _value; }
	__declspec(property(
                   get = value))
    const EntropyType Value;
	/*
	Константное свойство размера блока
	*/
    const size_t frame_size() { return _size; }
    __declspec(property(
                   get = frame_size))
    const size_t Size;
	/*
	Методы для добавления и удаления байта из блока - нужны 
	для быстрого пересчёта энтропии скользящего окна при его движении по области памяти.
	Неплохо бы добавить такие же методы для последовательностей байт, но здесь нам это не нужно.
	*/
    EntropyType append_byte(unsigned char val);
    EntropyType reduce_byte(unsigned char val);
};

/*
Объявляем типы абсциссы и ординаты графика.
Декларация условная: там, где мы обращаемся к значению оси X (абсциссы),
будет использоваться EntropyX, а там, где обращаемся к значению ф-и (ординаты, оси Y) - 
EntropyY. Эти типы можно объявить иначе, например, 
EntropyX можно без потери точности алгоритма сделать float.
*/
typedef EntropyType EntropyX, EntropyY;
/*
Тип, описывающий характеристики энтропии для заданной точки X, точнее, для окна 
(в нашем случае размером 512 байт), серединой которого является точка X.
5 графиков:
 - энтропия
 - производная
 - плотность максимумов
 - плотность минимумов
 - волатильность
*/
typedef struct EntropyCharacteristics {
    EntropyY entropy_value;//Собственно энтропия окна, серединой которого является точка X
    EntropyY entropy_derivative_value;//Значение первой производной энтропии в данной точке
    EntropyY maximums_density;//Количество максимумов в данном окне
    EntropyY minimums_density;//Количество минимумов в данном окне.
	//Должно быть приблизительно равно значению предыдущего поля, т.к. за минимумом следует максимум.
	//Общее количество экстремумов вычисляется, как сумма двух предыдущих полей.
    EntropyY volatility;//Волатильность - разница между самым большим и самым маленьким 
	//значением энтропии в данном окне, пока не используется и не рассчитывается
} EntropyChars, EntropyPoint;

//Перечисление, обозначающее состояние графика энтропии: спад, плато и рост соотв.
enum EntropyDirection { edirMax = -1 /*за максимумом начинается спад*/, 
	edirNo = 0/*плато*/, 
	edirMin = 1/*за минимумом начинается рост*/ };

inline EntropyDirection e_sign(const EntropyType c_val) {//Ф-я приведения дельты производной к типу EntropyDirection
    return ((c_val < 0) ? edirMax : ((c_val > 0) ? edirMin : edirNo));
}
//Расчёт направления графика по двум точкам производной
inline EntropyDirection e_dir(const EntropyY prev, const EntropyY cur) {
    if(prev * cur < 0)//Если производная пересекла 0 в любом направлении, это значение будет отрицательным
        return e_sign(cur - prev);
    else
        return edirNo;
}

/*
Типы и функции для визуализации графиков
*/

//Описатель экстремума
typedef struct ExtremumPoint {
	EntropyX X;
	EntropyY Y;
	EntropyDirection eDir;
	ExtremumPoint(EntropyX x = 0., EntropyY y = 0.,
		EntropyDirection edir = edirNo) : X(x), Y(y),
		eDir(edir)
	{}
} *PExtremumPoint;

#ifdef QT_CORE_LIB
/*
Определения, ориентированые на использование Qt
*/
typedef QVector<EntropyPoint> EntropyDiagram;//Тип диаграммы, содержащий значения для всех графиков
//Расчёт волатильности - пока не используется
inline EntropyY volatility(EntropyDiagram &diagram, const size_t cX, const size_t cWindowSz = cDefaultWindowSz) {
    const size_t cWinHalfSz = cWindowSz >> 1;
    EntropyY e_min = diagram[cX].entropy_value;
    EntropyY e_max = diagram[cX].entropy_value;
    for(int i = (int)(cX - cWinHalfSz); i < (int)(cX + cWinHalfSz); ++i) {
        if(i < 0) continue;
        if(i >= diagram.size())
            break;
        e_max = qMax(e_max, diagram[i].entropy_value);
        e_min = qMin(e_min, diagram[i].entropy_value);
    }
    return e_max - e_min;
}
//График экстремумов
typedef QVector<ExtremumPoint> ExtremumPoints;

#else
//Если используем stl вместо Qt
typedef std::vector<EntropyPoint> EntropyDiagram;
typedef std::vector<ExtremumPoint> ExtremumPoints;
#endif

#endif
