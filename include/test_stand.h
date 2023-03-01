#pragma once
#include <iostream>
//T - ����� ���������, E - ��� ��������� ������� ����� ����������
template <class T, typename E>
class Test_stand {
	T engine; //��������� ������� �� ����� �����������
	E (T::*method_ptr)() ; //��������� �� �����, ������� ����� ���������� �����
	string parameter_name;	//����� ������� ����� 
	double time_step_seconds; // ��� ���������
public:
	//engine - ��������� ������� �� ����� �����������, method_ptr - ��������� �� �����, ������� ����� ���������� �����,time_step_seconds - ��� ���������
	Test_stand(T engine, E (T::* method_ptr)(), double time_step_seconds) {
		this->engine = engine;
		this->method_ptr = method_ptr;
		this->time_step_seconds = time_step_seconds;
		this->parameter_name = "tracked parameter";
	}
	//engine - ��������� ������� �� ����� �����������, method_ptr - ��������� �� �����, ������� ����� ���������� �����,time_step_seconds - ��� ���������,  parameter_name - ��� ������������ ���������
	Test_stand(T engine, E(T::*method_ptr)(), double time_step_seconds, string parameter_name):Test_stand(engine, method_ptr, time_step_seconds) {
		this->parameter_name = parameter_name;
	}
	double start_simulation();
};

//���������� ��������� ��� IC_Engine
double Test_stand<IC_Engine, double>::start_simulation() {
	cout << endl << "Engine started" << endl;
	cout << "---------------" << endl;;
	Engine::engine_status status = Engine::engine_status::OK;
	double timer = -time_step_seconds; // ����� �������� � 0 � �� ���� +1 ���� ����� �����
	while (status == Engine::engine_status::OK) {
		status = this->engine.simulate_step(this->time_step_seconds);
		timer += time_step_seconds;
		cout << "time" << timer << " "<<parameter_name<<": " << (this->engine.*method_ptr)() << " status : " << status << endl;
	}
	cout << "time from start:" << timer << " seconds";
	return timer;
}