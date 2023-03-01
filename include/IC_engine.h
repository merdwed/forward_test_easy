#pragma once
#include "engine.h"
#include <vector>
using namespace std;

class IC_Engine :public Engine{
protected:
    double I ;          //Момент инерции двигателя (кг / м ^ 2)
    vector<double> M_func;//M компонент кусочной функции - крутящий момент вырабатываемого двигателем(Н * м), зависит от V
    vector<double> V_func;//V компонент кусочной функции - скорость вращения коленвала (радиан / сек)
    double HM ;         //Коэффициент зависимости скорости нагрева от крутящего момента (𝐶∙ / (𝐻 * м * сек))
    double HV ;         //Коэффициент зависимости скорости нагрева от скорости вращения коленвала (𝐶∙ * сек / рад2)
    
    double V_current;    //текущая скорость коленвала
    double calculate_M();
    double calculate_crankshaft_acceleration();
    double calculate_heating_rate();
public:
    
	IC_Engine(double T_air);
    IC_Engine(double I, vector<double> M_func, vector<double> V_func, double T_max, double HM, double HV, double C, double T_air);
    engine_status simulate_step(double time_step_seconds);
    double get_V_current();
};
