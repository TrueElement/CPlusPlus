#ifndef SUPER_NETWORK_H
#define SUPER_NETWORK_H
#include <string>
#include <sstream>
#include <iostream>
#include "Network.hpp"
template<typename X> class SuperNetwork : public Network<X> {
public:
	SuperNetwork();
	SuperNetwork(Scheduler<X,X> *sched);
	virtual void setScheduler(Scheduler<X,X> *sched);
	virtual Scheduler<X,X> * getScheduler();
	virtual void addInput(double real_time, int discrete_time, X input);
	virtual void setup();
	virtual void print();
	virtual void step();
	virtual void step(int n);
	virtual void batchStep();
	virtual void computeChildren();
	virtual void output();
	virtual void start();
	virtual X getOutput();
	virtual std::string toString();
	virtual ~SuperNetwork();
protected:
	Scheduler<X,X> *sched;
	std::stringstream *ss;
	X Output;
};

template<typename X> inline SuperNetwork<X>::SuperNetwork() {
	ss = new std::stringstream();
	sched = 0;
}

template<typename X> inline SuperNetwork<X>::SuperNetwork(Scheduler<X,X> *sched) {
	ss = new std::stringstream();
	this->sched = sched;
}

template<typename X> inline void SuperNetwork<X>::setScheduler(Scheduler<X, X>* sched) {
	this->sched = sched;
}

template<typename X> inline Scheduler<X, X> * SuperNetwork<X>::getScheduler() {
	return sched;
}

template<typename X> inline void SuperNetwork<X>::setup() {
	return;
}

template<typename X> inline void SuperNetwork<X>::print() {
	std::cout << ss->str();
	std::cout << std::endl;
}

template<typename X> inline void SuperNetwork<X>::step() {
	return;
}

template<typename X> inline void SuperNetwork<X>::step(int n) {
	for(int i = 0; i < n; i++) {
		step();
	}
}

template<typename X> inline void SuperNetwork<X>::batchStep() {
	while(sched->hasEvent() == true) {
		step();
	}
}

template<typename X> inline void SuperNetwork<X>::output() {
	std::cout << ss->str();
	std::cout << std::endl;

}

template<typename X> inline X SuperNetwork<X>::getOutput() {
	return Output;
}

template<typename X> inline std::string SuperNetwork<X>::toString() {
	return ss->str();
}

template<typename X> inline void SuperNetwork<X>::start() {
	return;
}

template<typename X> inline void SuperNetwork<X>::computeChildren() {
	return;
}

template<typename X>
inline void SuperNetwork<X>::addInput(double real_time, int discrete_time,
		X input) {
}

template<typename X> inline SuperNetwork<X>::~SuperNetwork() {
	delete[] ss;
}

#endif
