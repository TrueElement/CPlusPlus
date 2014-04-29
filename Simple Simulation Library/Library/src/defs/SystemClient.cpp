#include "../../include/defs/SystemClient.hpp"

SystemClient::SystemClient() {
	parts = 0;
	real_time = 0;
	discrete_time = 0;
	time = NULL;
	model = 0;
}

void SystemClient::input() {
	std::cout << "Real Discrete Parts:";
	std::cin >> real_time >> discrete_time >> parts;
	s_net->addInput(real_time, discrete_time, parts);
	std::cout << std::endl;
}

void SystemClient::inputn() {
	int count;
	std::cout << "How Many Input? ";
	std::cin >> count;
	std::cout << std::endl;
	for(int i = 0; i < count; i++) {
		input();
	}
}

void SystemClient::output() {
	std::cout << model->getOutput();
	std::cout << std::endl;
}

void SystemClient::print() {
	std::cout << model->toString();
	std::cout << std::endl;
}

SystemClient::~SystemClient() {
}


