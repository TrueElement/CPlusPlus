#ifndef ATOMIC_H
#define ATOMIC_H
#include <string>
#include <sstream>
#include <vector>
#include "../sim/Time2D.hpp"
#include "../sim/Pair.hpp"

template<typename X> class Atomic {
public:
	Atomic();
    Atomic(std::string name);
    Atomic(std::string name, std::string type);
    void setName(std::string name);
    std::string getName();
    void setType(std::string type);
    std::string getType();
    void setInput(int index, X input);
    X getInput(int index);
    X getOutput(int index);
    Time2D * getExpireTime();
    Time2D * getLastTime();
    void setExpireTime(double real_time, int discrete_time);
    virtual Atomic<X>& operator=(Atomic<X> rhs);
    virtual bool operator< (const Atomic<X> & rhs);
    virtual bool operator== (const Atomic<X> & rhs);
    virtual void timeAdvance(int p, double s);
	virtual X deltaInternal();
	virtual void deltaExternal(Time2D *time, X *input);
	virtual X deltaConf(X *input);
	virtual X delta(Time2D *time, X *input);
	virtual X lambda();
    virtual X getOutput();
    virtual void compute();
    virtual std::string toString();
	virtual ~Atomic();
protected:
    std::string name;
    std::string type;
    std::vector<X> *inputarr;
    std::vector<X> *outputarr;
    Time2D *expire;
    Time2D *last;
};

template<typename X> class AtomicCompare {
public:
	int operator() (Atomic<X>* const& lhs, Atomic<X>* const& rhs) {
		Time2D *lhs_time = lhs->getExpireTime();
		Time2D *rhs_time = rhs->getExpireTime();

		int cmp;
		if(*lhs_time < *rhs_time) {
			cmp = -1;
		} else if(*lhs_time == *rhs_time) {
			cmp = 0;
		} else {
			cmp = 1;
		}
		return cmp;
	}
};

template<typename X> Atomic<X>::Atomic() {
	name = "Generic";
	type = "Generic";
	inputarr = new std::vector<X>();
	outputarr = new std::vector<X>();
	expire = new Time2D(0.0,0);
	last = new Time2D(0.0,0);
}

template<typename X> Atomic<X>::Atomic(std::string name) {
	this->name = name;
	inputarr = new std::vector<X>();
	outputarr = new std::vector<X>();
	expire = new Time2D(0.0,0);
	last = new Time2D(0.0,0);
}

template<typename X> Atomic<X>::Atomic(std::string name, std::string type) {
	this->name = name;
	this->type = type;
	inputarr = new std::vector<X>();
	outputarr = new std::vector<X>();
	expire = new Time2D(0,0);
	last = new Time2D(0.0,0);
}

template<typename X> void Atomic<X>::setName(std::string name) {
    this->name = name;
}


template<typename X> std::string Atomic<X>::getName() {
    return name;
}

template<typename X> void Atomic<X>::setType(std::string type) {
    this->type = type;
}

template<typename X> std::string Atomic<X>::getType() {
    return type;
}

template<typename X> void Atomic<X>::timeAdvance(int p, double s) {

}

template<typename X> X Atomic<X>::deltaInternal() {
	return 0;
}

template<typename X> X Atomic<X>::deltaConf(X *input) {
	return 0;
}

template<typename X> void Atomic<X>::deltaExternal(Time2D *time, X *input) {
	return;
}

template<typename X> X Atomic<X>::delta(Time2D *time, X *input) {
	if(input == NULL) {
		return deltaInternal();
	}

	if(*last < *time && *time < *expire) {
		deltaExternal(time, input);
	}

	if(*time == *expire) {
		return deltaConf(input);
	}
	return 0;
}

template<typename X> X Atomic<X>::lambda() {
	return 0;
}

template<typename X> Time2D * Atomic<X>::getExpireTime() {
	return this->expire;
}

template<typename X> Time2D * Atomic<X>::getLastTime() {
	return this->last;
}

template<typename X> void Atomic<X>::setExpireTime(double real_time, int discrete_time) {
	expire->setRealTime(real_time);
	expire->setDiscreteTime(discrete_time);
}

template<typename X> X Atomic<X>::getOutput() {
	return 0;
}


template<typename X> std::string Atomic<X>::toString() {
    std::stringstream ss;
        ss << name << "-" << type;
    return ss.str();
}



template<typename X> void Atomic<X>::setInput(int index, X input) {
	if(inputarr->size() <= index) {
		return;
	} else {
		inputarr[index] = input;
	}
}

template<typename X> X Atomic<X>::getInput(int index) {
	return inputarr[index];
}

template<typename X> X Atomic<X>::getOutput(int index) {
	return outputarr[index];
}

template<typename X> bool Atomic<X>::operator< (const Atomic<X>& rhs) {
	return expire < rhs.expire;
}

template<typename X> bool Atomic<X>::operator== (const Atomic<X>& rhs) {
	return expire == rhs.expire;
}

template<typename X> Atomic<X>& Atomic<X>::operator= (Atomic<X> rhs) {
	inputarr = rhs.inputarr;
	outputarr = rhs.outputarr;
	name = rhs.name;
	type = rhs.type;
	expire = rhs.expire;
	return *this;
}

template<typename X> inline void Atomic<X>::compute() {
	return;
}

template<typename X> Atomic<X>::~Atomic() {
	delete[] inputarr;
	delete[] outputarr;
}

#endif
