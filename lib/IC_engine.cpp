#include "../include/IC_Engine.h"
void IC_Engine::set_default_parameters() {
    this->I = 10;
    this->M_func = { 20, 75, 100, 105, 75, 0 };
    this->V_func = { 0, 75, 150, 200, 250, 300 };
    this->T_max = 110;
    this->HM = 0.01;
    this->HV = 0.0001;
    this->C = 0.1;
}
IC_Engine::IC_Engine() :Engine(){
    set_default_parameters();
}
IC_Engine::IC_Engine(double T_air) :Engine(T_air){
    set_default_parameters();
}
IC_Engine::IC_Engine(double I, vector<double> M_func, vector<double> V_func, double T_max, double HM, double HV, double C, double T_air) :Engine(T_max, T_air) {
    this->I = I;
    this->M_func = M_func;
    this->V_func = V_func;
    this->HM = HM;
    this->HV = HV;
    this->C = C;
}
double IC_Engine::calculate_M() {
    int i = 1;
    //по окончанию цикла V_current лежит между V_func[i-1] и V_func[i] или за пределами Vfunc
    for (; i < V_func.size() && V_current > V_func[i]; ++i);
    if (i == V_func.size())
        return 0;
    int right = i;
    int left = i - 1;
    // классическое уравнение прямой
    double M = (V_current - V_func[left]) / (V_func[right] - V_func[left]) * (M_func[right] - M_func[left]) + M_func[left];
    return M;
}

double IC_Engine::calculate_crankshaft_acceleration() {
    return calculate_M() / I;
}

double IC_Engine::calculate_heating_rate() {
    return calculate_M() * this->HM * this->V_current * this->V_current * this->HV;
}

IC_Engine::engine_status IC_Engine::simulate_step(double time_step_seconds) {
    if (T_current >= T_max)
        return engine_status::OVERHEATED;
    T_current += (calculate_heating_rate() + calculate_cooling_rate()) * time_step_seconds;
    V_current += calculate_crankshaft_acceleration() * time_step_seconds;
    if (T_current >= T_max)
        return engine_status::OVERHEATED;
    return engine_status::OK;
}


double IC_Engine::get_V_current() {
    return this->V_current;
}

std::ostream& operator<<(std::ostream& os, const IC_Engine::engine_status Status){
    switch (Status)
    {
    case IC_Engine::engine_status::OK:
        os << "OK";
        break;
    case IC_Engine::engine_status::OVERHEATED:
        os << "OVERHEATED";
        break;
    }
    return os;
}