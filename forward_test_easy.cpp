#include "dist/json/json.h"
#include "include/IC_engine.h"
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
void read_json_configuration() {
    ifstream file("stand_config.json");
    if (file.is_open()) {
        Json::Value json_root;
        Json::Value json_temp;
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
    }
}
int main()
{
    read_json_configuration();

    cout << "enter current temperature of air:";
    double T_air;
    cin >> T_air;
    IC_Engine engine(I, M_func, V_func, T_max, HM, HV, C, T_air);
    cout << "engine configuration" << endl;
    cout << "I: " << I << endl;
    cout << "M_func: ";
    for (double i : M_func)
        std::cout << i << ' ';
    cout << endl;
    cout << "V_func: ";
    for (double i : M_func)
        std::cout << i << ' ';
    cout << endl;
    cout << "T_max: " << T_max << endl;
    cout << "HM: " << HM << endl;
    cout << "HV: " << HV << endl;
    cout << "C: " << C << endl;
    cout << endl << "Engine started" << endl;
    cout << "---------------" << endl;;
    Engine::engine_status status = Engine::engine_status::OK;
    double timer = 0;
    while (status == Engine::engine_status::OK) {
        status = engine.simulate_step(time_step_seconds);
        cout << "time" << timer << " temperature: " << engine.get_T_current() << " status:" << status << endl;
        timer += time_step_seconds;
    }
    cout << "time from start:" << timer << " seconds";
}