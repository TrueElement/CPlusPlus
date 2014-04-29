#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <string>
#include "../model/Network.hpp"
#include "../model/SuperNetwork.hpp"
#include "Scheduler.hpp"

template<typename X, typename Y> class Client {
public:
	Client() {
		this->sched = NULL;
		this->model = NULL;
		this->s_net = 0;
	}

	void setScheduler(Scheduler<X, Y> *sched) {
		this->sched = sched;
	}

	virtual void setModel(Network<X> *model) {
		this->model = model;
	}

	virtual void setSuperNetwork(SuperNetwork<X> *s_net) {
		this->s_net = s_net;
	}

	void startCLI() {
		std::string input;
		while(true) {
			std::cout << "Enter Command:";
			std::cin >> input;
			std::cout << std::endl;
			processCommand(input);
		}
	}

	virtual void processCommand(std::string input) {
		if(input.compare("q") == 0) {
			exit(0);
		} else if(input.compare("s") == 0) {
			step();
		} else if(input.compare("sn") == 0) {
			stepn();
		} else if(input.compare("i") == 0) {
			this->input();
		} else if(input.compare("in") == 0) {
			inputn();
		} else if(input.compare("o") == 0) {
			output();
		} else if(input.compare("p") == 0) {
			print();
		} else if(input.compare("b") == 0) {
			batch();
		} else if(input.compare("ts") == 0) {
			timeStep();
		} else if(input.compare("tsn") == 0) {
			timeStepN();
		}
	}
	virtual void input() {
		return;
	}
	virtual void inputn() {
		return;
	}

	virtual void output() {
		return;
	}

	virtual void print() {
		return;
	}

	void batch() {
		sched->batch();
	}

	virtual void step() {
		sched->step();
	}

	virtual void timeStep() {
		sched->timeStep();
	}

	virtual void timeStepN() {
		int steps;
		std::cout << "How many steps? ";
		std::cin >> steps;
		sched->timeStep(steps);
	}

	void stepn() {
		int steps;
		std::cout << "How many steps? ";
		std::cin >> steps;
		sched->step(steps);
	}

	virtual ~Client() {
		delete[] sched;
	}
protected:
	Scheduler<X, Y> *sched;
	Network<X> *model;
	SuperNetwork<X> *s_net;
};
#endif
