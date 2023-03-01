#include "dist/json/json.h"
#include "include/engine.h"
#include "include/IC_engine.h"
#include "include/test_stand.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
//шаг симуляции
double time_step_seconds = 0.002;



//Момент инерции двигателя (кг / м ^ 2)
double I = 10;
//M компонент кусочной функции - крутящий момент вырабатываемого двигателем(Н * м), зависит от V
vector<double> M_func = { 20, 75, 100, 105, 75,  0 };
//V компонент кусочной функции - скорость вращения коленвала (радиан / сек)
vector<double> V_func = { 0,  75, 150, 200, 250, 300 };
//температура перегрева двигателя
double T_max = 110;
//Коэффициент зависимости скорости нагрева от крутящего момента (𝐶∙ / (𝐻 * м * сек))
double HM = 0.01;
//Коэффициент зависимости скорости нагрева от скорости вращения коленвала (𝐶∙ * сек / рад2)
double HV = 0.0001;
//Коэффициент зависимости скорости охлаждения от температуры двигателя и окружающей среды (1 / сек)
double C = 0.1;
Json::Value json_root;
Json::Value json_temp;
void read_json_configuration() {
    ifstream file("config.json");
    if (file.is_open()) {
        
        file >> json_root;
        I = json_root["IC_engine"]["I"].asDouble();
        M_func.clear();
        json_temp = json_root["IC_engine"]["M_func"];
        transform(json_temp.begin(), json_temp.end(), back_inserter(M_func), [](const auto& e) { return e.asDouble(); });
        V_func.clear();
        json_temp = json_root["IC_engine"]["V_func"];
        transform(json_temp.begin(), json_temp.end(), back_inserter(V_func), [](const auto& e) { return e.asDouble(); });
        T_max = json_root["IC_engine"]["T_max"].asDouble();
        HM = json_root["IC_engine"]["HM"].asDouble();
        HV = json_root["IC_engine"]["HV"].asDouble();
        C = json_root["IC_engine"]["C"].asDouble();

        time_step_seconds = json_root["simulation"]["time_step_seconds"].asDouble();
        cout << "configuration data has been read. Setted parameters:" << endl;
        cout << json_root << endl;
    }
    else {
        cout << "file \"config.json\" not found. default parameters are used" << endl;
    }
}
int main()
{
    read_json_configuration();
    
    double T_air;
    cout << "enter current temperature of air:";
    cin >> T_air;
    
    IC_Engine engine(I, M_func, V_func, T_max, HM, HV, C, T_air);
    
    //стенд сделан через шаблоны. Конструктору даётся двигатель, функция которую надо мониторить, шаг симуляции и имя параметра (не обязательно)
    Test_stand<IC_Engine, double> stand(engine, &IC_Engine::get_T_current, time_step_seconds, "temperature");
    stand.start_simulation();
}