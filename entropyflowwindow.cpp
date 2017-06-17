#include "entropyflowwindow.h"
#include <QMessageBox>

EntropyFlowWindow::EntropyFlowWindow(unsigned char *Area,
                                     size_t AreaSz,
                                     size_t WindowSz,
                                     QObject *parent) : QObject(parent),
    cWindowSz(WindowSz)
{
	/*
	Конструктор принимает на вход область памяти и размер окна, по умолчанию 512 байт.
	Уславливаемся, что движение окна от начала области памяти к концу - "снизу вверх", в область более старших адресов.
	*/
    const size_t cWinHalfSz = cWindowSz >> 1;//Размер половины окна
    points.resize(AreaSz);//Выделяем память под точки диаграммы. Длина диаграммы численно равна длине блока памяти.
	//Делать resize сразу быстрее, чем делать push_back для каждой следующей точки.
    if(cWinHalfSz < AreaSz) {
		/*
		Декларируем массивы значений графиков плотности экстремумов
		*/
        ExtremumPoints maximums;
        ExtremumPoints minimums;
        Entropy entropy(Area, cWinHalfSz);
		/*
		Поскольку ниже нулевой точки графика ничего нет, считаем энтропию для окна половинного размера в начале блока.
		По мере движения точки-центра окно будет увеличиваться, пока не перестанет пересекать или соприкасаться с началом
		графика.
		*/
        points[0].entropy_value = entropy.Value;//Определяем значение нулевой точки графика
        points[0].entropy_derivative_value = 0.;
        points[0].maximums_density = 0.;
        points[0].minimums_density = 0.;
		/*
		В этом цикле скользящее окно движется по всей области памяти, 
		рассчитывая одной процедурой все значения для точки-центра скользящего окна
		*/
        for(size_t i = 1; i < AreaSz; ++i) {
            const EntropyX c_abs = (EntropyX)i;//Приводим счётчик цикла к значению абсциссы (с плавающей точкой)
            EntropyPoint &pt = points[i];//Ссылка на точку графика
            EntropyY entropy_value = entropy.Value;
			//Движение окна на байт вверх по области памяти:
            if(c_abs < (EntropyX)AreaSz - (EntropyX)cWinHalfSz)//только если окно не упёрлось в верхнюю границу блока...
                entropy.append_byte(*(Area + PRED(cWinHalfSz) + i));//добавляем следующий байт...
            if(c_abs > cWinHalfSz)//только если окно не соприкасается и не пересекает начало - нижнюю границу блока...
                entropy.reduce_byte(*(Area - SUCC(cWinHalfSz) + i));//удаляем первый байт
			//...окно передвинулось на байт вверх, все значения для точки-центра скользящего окна пересчитаны.
            pt.entropy_value = entropy.Value;
			//Сразу же рассчитываем значение производной
            const EntropyY c_cur_delta =
                    pt.entropy_value - entropy_value;
            pt.entropy_derivative_value = c_cur_delta;
			//И сразу же ищем экстремумы
            const EntropyY c_prev_delta = points[PRED(i)].entropy_derivative_value;
            switch(const EntropyDirection edir = e_dir(c_prev_delta, c_cur_delta))
            {
            case edirMax:
            {
				//Нашли максимум
                maximums.push_back(
                            ExtremumPoint(c_abs,
                                          pt.entropy_value,
                                          edir));
                break;
            }
            case edirMin:
            {
				//Нашли минимум
                minimums.push_back(
                            ExtremumPoint(c_abs,
                                          pt.entropy_value,
                                          edir));
                break;
            }
            case edirNo:
				//Не нашли
            default:
                break;
            }
			//Мы ещё не нашли все экстремумы для текущего положения окна.
			//Расчёт плотности экстремумов, но не для точки-центра скользящего окна, в котором она ещё неизвестна,
			//а для нижней границы окна, в которой она уже известна
            if(c_abs > cWinHalfSz) {//Если окно "отъехало" от начала графика
				//Точка нижней границы окна, соответствует положению окна на пол-окна ниже, для которого рассчитывается плотность экстремумов.
                const EntropyX c_extremum_calc_x = c_abs - cWinHalfSz;
				/*
				Поскольку мы рассчитываем плотность экстремумов не для текущего окна, а для его 
				позиции на пол-окна ниже, мы должны использовать размер окна именно в той точке.
				*/
                const EntropyX cFrameSz =
                        c_extremum_calc_x > cWinHalfSz ?
                            (EntropyX)cWindowSz :
                            cWinHalfSz + c_extremum_calc_x;
                const EntropyX c_lower = c_abs - (EntropyX)cWindowSz;//Нижняя граница окна для точки c_extremum_calc_x
				//Отбрасываем все экстремумы, которые больше не входят в обсчитываемое окно после изменения его положения
                while(minimums.size() && minimums[0].X < c_lower)
                    minimums.remove(0);
                while(maximums.size() && maximums[0].X < c_lower)
                    maximums.remove(0);
				//Вычисляем значения плотности экстремумов
                EntropyPoint &pt = points[c_extremum_calc_x];
                pt.maximums_density = maximums.size() / cFrameSz;
                pt.minimums_density = minimums.size() / cFrameSz;
            }
        }
		//Поскольку мы рассчитываем плотности экстремумов с отставанием, 
		//процедура обсчёта плотности за пол-окна до верхней границы блока, 
		//поэтому досчитываем оставшийся кусок графика
        for(size_t i = AreaSz - cWinHalfSz; i < AreaSz; ++i) {
            const EntropyX c_extremum_calc_x = (EntropyX)i;
            const EntropyX cFrameSz = AreaSz - i + cWinHalfSz;
            const EntropyX c_lower = c_extremum_calc_x - (EntropyX)cWindowSz;

            while(minimums.size() && minimums[0].X < c_lower)
                minimums.remove(0);
            while(maximums.size() && maximums[0].X < c_lower)
                maximums.remove(0);

            EntropyPoint &pt = points[c_extremum_calc_x];
            pt.maximums_density = maximums.size() / cFrameSz;
            pt.minimums_density = minimums.size() / cFrameSz;
            //pt.volatility = volatility(points, c_extremum_calc_x);
        }
    } else {
        //Если размер области памяти меньше, чем размер плавающего окна,
		//считаем, что у нас плато. Рассчитываем энтропию для всего блока
		//и заполняем график этим значением, при этом производной, 
		//минимумами и максимумами пренебрегаем.
        Entropy entropy(Area, AreaSz);
        for(size_t i = 0; i < AreaSz; ++i) {
            points[i] = EntropyPoint({entropy.Value, 0., 0., 0., 0.});
        }
    }
}

EntropyDiagram EntropyFlowWindow::get_points() { return points; }
