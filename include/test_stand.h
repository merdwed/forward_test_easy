#pragma once
#include <iostream>
//T - класс двигателя, E - тип параметра который нужно мониторить
template <class T, typename E>
class Test_stand {
	T engine; //двигатель который мы будем тестировать
	E (T::*method_ptr)() ; //указатель на метод, который будет мониторить стенд
	string parameter_name;	//текст который будет 
	double time_step_seconds; // шаг симуляции
public:
	//engine - двигатель который мы будем тестировать, method_ptr - указатель на метод, который будет мониторить стенд,time_step_seconds - шаг симуляции
	Test_stand(T engine, E (T::* method_ptr)(), double time_step_seconds) {
		this->engine = engine;
		this->method_ptr = method_ptr;
		this->time_step_seconds = time_step_seconds;
		this->parameter_name = "tracked parameter";
	}
	//engine - двигатель который мы будем тестировать, method_ptr - указатель на метод, который будет мониторить стенд,time_step_seconds - шаг симуляции,  parameter_name - имя исследуемого параметра
	Test_stand(T engine, E(T::*method_ptr)(), double time_step_seconds, string parameter_name):Test_stand(engine, method_ptr, time_step_seconds) {
		this->parameter_name = parameter_name;
	}
	double start_simulation();
};

//реализация конкретно для IC_Engine
double Test_stand<IC_Engine, double>::start_simulation() {
	cout << endl << "Engine started" << endl;
	cout << "---------------" << endl;;
	Engine::engine_status status = Engine::engine_status::OK;
	double timer = -time_step_seconds; // чтобы началось с 0 и не было +1 степ после конца
	while (status == Engine::engine_status::OK) {
		status = this->engine.simulate_step(this->time_step_seconds);
		timer += time_step_seconds;
		cout << "time" << timer << " "<<parameter_name<<": " << (this->engine.*method_ptr)() << " status : " << status << endl;
	}
	cout << "time from start:" << timer << " seconds";
	return timer;
}