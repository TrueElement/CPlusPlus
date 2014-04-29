#include "../../include/defs/AutomataClient.hpp"

AutomataClient::AutomataClient() {
	automata = 0;
}

void AutomataClient::input() {
	int cell_num, value;
	std::cout << "Cell # - Value: ";
	std::cin >> cell_num >> value;

}

void AutomataClient::inputn() {
	int num;
	std::cout << "Enter number of inputs:";
	std::cin >> num;
	std::cout << std::endl;
	for(int i = 0; i < num; i++) {
		input();
	}
}

void AutomataClient::output() {
	s_net->output();
}

void AutomataClient::print() {
	s_net->print();
}

void AutomataClient::step() {
	s_net->step();
}

AutomataClient::~AutomataClient() {
}
