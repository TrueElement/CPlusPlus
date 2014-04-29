#ifndef AUTOMATA_CLIENT_H
#define AUTOMATA_CLIENT_H
#include "../sim/Client.hpp"
#include "Automata.hpp"
class AutomataClient : public Client<int, int> {
public:
	AutomataClient();
	void input();
	void inputn();
	void output();
	void print();
	void step();
	~AutomataClient();
private:
	Automata *automata;
};
#endif
