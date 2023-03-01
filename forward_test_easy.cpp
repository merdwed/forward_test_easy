#include "dist/json/json.h"
#include <fstream>
using namespace std;
#include <iostream>
#include <algorithm>

int main()
{
    ifstream file("stand_config.json");
    Json::Value jsonRoot;
    file >> jsonRoot;

    double I = jsonRoot["engine"]["I"].asDouble(); //Момент инерции двигателя (кг / м ^ 2)
    vector<double> M; //крутящий момент вырабатываемого двигателем(Н * м), зависим от V
    transform(jsonRoot["engine"]["M"].begin(), jsonRoot["engine"]["M"].end(), std::back_inserter(M), [](const auto& e) { return e.asDouble(); });
    vector<double> V ; //скорости вращения коленвала (радиан / сек)
    transform(jsonRoot["engine"]["V"].begin(), jsonRoot["engine"]["V"].end(), std::back_inserter(V), [](const auto& e) { return e.asDouble(); });
    double Tmax = jsonRoot["engine"]["Tmax"].asDouble(); //температура перегрева двигателя
    double HM = jsonRoot["engine"]["HM"].asDouble(); //Коэффициент зависимости скорости нагрева от крутящего момента (𝐶∙ / (𝐻 * м * сек))
    double HV = jsonRoot["engine"]["HV"].asDouble(); //Коэффициент зависимости скорости нагрева от скорости вращения коленвала (𝐶∙ * сек / рад2)
    double C = jsonRoot["engine"]["C"].asDouble(); //Коэффициент зависимости скорости охлаждения от температуры двигателя и окружающей среды (1 / сек)


    cout << "I " << I << endl;
    cout << "M ";
    for (double i : M)
        std::cout << i << ' ';
    cout << endl;
    cout << "V ";
    for (double i : M)
        std::cout << i << ' ';
    cout << endl;
    cout << "Tmax " << Tmax << endl;
    cout << "HM " << HM << endl;
    cout << "HV " << HV << endl;
    cout << "C " << C << endl;

   
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
