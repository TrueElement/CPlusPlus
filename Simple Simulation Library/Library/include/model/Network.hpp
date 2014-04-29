#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include <string>
#include "Atomic.hpp"
#include "Coupling.hpp"
#include "../sim/Scheduler.hpp"
#include "../sim/Event.hpp"

template<typename X> class Network : public Atomic<X> {
public:
	Network();
    Network(std::string name);
    Network(std::string name, std::string type);
    virtual void setScheduler(Scheduler<X,X> *sched);
    virtual void throwEvent();
    virtual void throwEvent(X out);
    virtual X getOutput();
    int getInputIndex();
    int getOutputIndex();
    virtual void setInput(int index, X value);
	void addInputCoupling(Coupling<X> *c);
	void addOutputCoupling(Coupling<X> *c);
	void translateInput();
	void translateOutput();
	void addConnection(Network<X> *con);
	virtual ~Network();
protected:
	Scheduler<X,X> *sched;
	std::vector<Coupling<X> *> *couplingIn;
    std::vector<Coupling<X> *> *couplingOut;
    std::vector<Network<X> *> *connections;
    int in_index;
    int out_index;
};


template<typename X> inline Network<X>::Network() {
    couplingOut = new std::vector<Coupling<X> *>();
    couplingIn = new std::vector<Coupling<X> *>();
    connections = new std::vector<Network<X> *>();
    in_index = 0;
    out_index = 0;
    sched = 0;
}

template<typename X> inline Network<X>::Network(std::string name) {
    couplingOut = new std::vector<Coupling<X> *>();
    couplingIn = new std::vector<Coupling<X> *>();
    connections = new std::vector<Network<X> *>();
    in_index = 0;
    out_index = 0;
    sched = 0;
}

template <typename X> inline Network<X>::Network(std::string name, std::string type) {
    couplingOut = new std::vector<Coupling<X> *>();
    couplingIn = new std::vector<Coupling<X> *>();
    connections = new std::vector<Network<X> *>();
    in_index = 0;
    out_index = 0;
    sched = 0;
}

template <typename X> inline X Network<X>::getOutput() {
	return this->outputarr->at(0);
}

template<typename X> inline void Network<X>::addInputCoupling(Coupling<X> *c) {
	c->setDestIndex(in_index);
    couplingIn->push_back(c);
    in_index++;
}

template<typename X> inline void Network<X>::addOutputCoupling(Coupling<X> *c) {
	c->setSourceIndex(out_index);
    couplingOut->push_back(c);
    out_index++;

}

template <typename X> inline void Network<X>::translateInput() {
    unsigned int i = 0;
    Coupling<X> *temp;
    for(i = 0; i < couplingIn->size(); i++) {
        temp = couplingIn->at(i);
        temp->translate();
    }
}

template <typename X> inline void Network<X>::translateOutput() {
    unsigned int i = 0;
    Coupling<X> *temp;
    for(i = 0; i < couplingOut->size(); i++) {
        temp = couplingOut->at(i);
        temp->translate();
    }
}

template<typename X> inline int Network<X>::getInputIndex() {
	return in_index;
}

template<typename X> inline int Network<X>::getOutputIndex() {
	return out_index;
}

template<typename X> inline void Network<X>::setInput(int index, X value) {
	this->inputarr->at(index) = value;
}

template<typename X> inline void Network<X>::setScheduler(Scheduler<X, X>* sched) {
	this->sched = sched;
}

template<typename X> inline void Network<X>::throwEvent() {
	return;
}

template<typename X> inline void Network<X>::throwEvent(X out) {
	return;
}

template<typename X> inline void Network<X>::addConnection(Network<X>* con) {
	connections->push_back(con);
}



template<typename X> inline Network<X>::~Network() {
	delete[] couplingOut;
	delete[] couplingIn;

}
#endif
