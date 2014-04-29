#ifndef EVENT
#define EVENT
template<typename X>  class Atomic;
#include <sstream>
#include "Time2D.hpp"

template<typename X> class Event {
public:
	Event();
	Event(Atomic<X> *linked, Time2D *time);
	Event(Atomic<X> *linked, double real_time, int discrete_time);
	Event(double real_time, int discrete_time);
	void setModel(Atomic<X> *linked);
	Atomic<X> * getModel();
	void setTime(Time2D *time);
	void setTime(double real_time, int discrete_time);
	void setInput(X input);
	X  getInput();
	bool hasInput();
	Time2D * getTime();
	bool operator <(Event *rhs);
	bool operator <(const Event &rhs) const;
	std::string toString();
	~Event();
private:
	Time2D *evt_time;
	Atomic<X> *linked;
	X input;
};

template<typename X> class EventCompare {
public:
	bool operator() (Event<X>* const& lhs, Event<X>* const& rhs) {
		Time2D *lhs_time = lhs->getTime();
		Time2D *rhs_time = rhs->getTime();

		if(lhs_time->getRealTime() == rhs_time->getRealTime()) {
			if(lhs_time->getDiscreteTime() > rhs_time->getDiscreteTime()) {
				return true;
			} else {
				return false;
			}
		} else {
			if(lhs_time->getRealTime() > rhs_time->getRealTime()) {
				return true;
			} else {
				return false;
			}
		}
	}
private:
};

template<typename X> inline Event<X>::Event() {
	linked = 0;
	evt_time = 0;
	input = 0;
}

template<typename X> inline Event<X>::Event(Atomic<X>* linked, Time2D* time) {
	this->linked = linked;
	this->evt_time = time;
	input = 0;
}

template<typename X> inline Event<X>::Event(Atomic<X>* linked, double real_time, int discrete_time) {
	this->linked = linked;
	this->evt_time = new Time2D(real_time, discrete_time);
	input = 0;
}

template<typename X> inline Event<X>::Event(double real_time, int discrete_time) {
	this->linked = 0;
	this->evt_time = new Time2D(real_time, discrete_time);
	input = 0;
}

template<typename X> inline void Event<X>::setModel(Atomic<X>* linked) {
	this->linked = linked;
}

template<typename X> inline Atomic<X>* Event<X>::getModel() {
	return this->linked;
}

template<typename X> inline void Event<X>::setTime(Time2D* time) {
	this->evt_time = time;
}

template<typename X> inline void Event<X>::setTime(double real_time, int discrete_time) {
	this->evt_time = new Time2D(real_time, discrete_time);
}

template<typename X> inline Time2D* Event<X>::getTime() {
	return this->evt_time;
}

template<typename X> inline bool Event<X>::operator<(Event* rhs) {
	Time2D *rhs_time = rhs->getTime();
	return *evt_time < *rhs_time;
}

template<typename X> inline bool Event<X>::operator<(const Event& rhs) const {
	Time2D *rhs_time = rhs.evt_time;
	return *evt_time < *rhs_time;
}

template<typename X> inline std::string Event<X>::toString() {
	std::stringstream ss;
	ss << "E-";
	ss << evt_time->toString();
	return ss.str();
}

template<typename X> inline void Event<X>::setInput(X input) {
	this->input = input;
}

template<typename X> inline X Event<X>::getInput() {
	return this->input;
}

template<typename X> inline bool Event<X>::hasInput() {
	if(this->input != 0) {
		return true;
	} else {
		return false;
	}
}

template<typename X> inline Event<X>::~Event() {
	delete[] evt_time;
}

#endif
