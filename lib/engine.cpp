#include "../include/engine.h"
Engine::Engine() :Engine(25){
	this->T_air = T_air;
	this->T_current = T_air;
}
Engine::Engine(double T_air) {
	set_T_air(T_air);
}
Engine::Engine(double T_max, double T_air):Engine(T_air) {
	this->T_max = T_max;      
}
void Engine::set_T_air(double T_air) {
	this->T_air = T_air;
	this->T_current = T_air;
}
double Engine::get_T_current() {
	return this->T_current;
}

double Engine::calculate_heating_rate() {
	return -calculate_cooling_rate(); //заглушка на нагрев
}

double Engine::calculate_cooling_rate() {
	return this->C * (this->T_air - this->T_current);
}
