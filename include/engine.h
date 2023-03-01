#pragma once
#include <ostream>
class Engine {
protected:
    double T_max;        //����������� ��������� ���������
    double T_air;        //����������� ������� �����
    double T_current;    //������� ����������� ���������
    double C;           //����������� ����������� �������� ���������� �� ����������� ��������� � ���������� ����� (1 / ���)
public:
    Engine();
    Engine(double T_air);
    Engine(double T_max, double T_air);
    enum class engine_status { OK, OVERHEATED };
    void set_T_air(double T_air);
    double get_T_current();
    double calculate_heating_rate();
    double calculate_cooling_rate();
};
std::ostream& operator<<(std::ostream& os, const Engine::engine_status Status);