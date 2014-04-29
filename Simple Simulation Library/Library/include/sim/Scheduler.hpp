#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "../heap/Heap.hpp"
#include "../model/Atomic.hpp"
#include "Event.hpp"
#include "Pair.hpp"
#include "Input.hpp"

template <typename X, typename Y> class Scheduler {
public:
	Scheduler();
	void addEvent(Event<X> *evt);
	void clearEvents();
	void injectInput(Atomic<X> *model, Time2D *time, X *input);
	void input(Event<X> *evt);
	void step();
	void timeStep();
	void timeStep(int n);
	void step(int n);
	void discreteTimeStep();
	void discreteTimeStep(int n);
	void batch();
	bool hasEvent();
	void setEventTrace(bool evt_trace);
	void eventTrace();
	void printQueue();
	Heap<Event<X> *> * getQueue();
	~Scheduler();
protected:
	Heap<Event<X> *, EventCompare<X> > *evt_queue;
	Atomic<X> *current;
	Event<X> *cevt;
	Time2D *clock;
	double current_time;
	bool evt_trace;

};

template<typename X, typename Y> Scheduler<X, Y>::Scheduler() {
	evt_queue = new Heap<Event<X> *, EventCompare<X> >();
	clock = new Time2D(0.0,0);
	current = 0;
	cevt = 0;
	current_time = 0.0;
	evt_trace = false;
}

template<typename X, typename Y> void Scheduler<X, Y>::addEvent(Event<X> *evt) {
	evt_queue->add(evt);
}

template<typename X, typename Y> void Scheduler<X, Y>::injectInput(Atomic<X> *model, Time2D *time, X *input) {
	Event<X> *input_event = new Event<X>();
		input_event->setModel(model);
		input_event->setTime(time);
		input_event->setInput(input);
	this->evt_queue->add(input_event);

}

template<typename X, typename Y> inline void Scheduler<X, Y>::eventTrace() {
	Time2D *time = current->getExpireTime();
	std::cout << "E-:" << current->getName();
	std::cout << ":T-" << time->getRealTime();
	std::cout << "-" << time->getDiscreteTime();
	std::cout << std::endl;
}

template<typename X, typename Y> void Scheduler<X, Y>::input(Event<X> *evt) {
	Atomic<X> *inp_mod = evt->getModel();
	clock = evt->getTime();
	X in = evt->getInput();
	X *input = &in;
	inp_mod->delta(clock, input);
}

template<typename X, typename Y> void Scheduler<X, Y>::step() {
	if(!evt_queue->isEmpty()) {
		cevt = evt_queue->poll();
		current = cevt->getModel();
		if(evt_trace == true) {
			this->eventTrace();
		}

		if(cevt->hasInput()) {
			input(cevt);
		} else {
			Time2D *evt_time = cevt->getTime();
			if(evt_time->getRealTime() < clock->getRealTime()) {
				current->delta(clock, 0);
			} else {
				clock = cevt->getTime();
					current->delta(clock, 0);
			}

		}
	}

}

template<typename X, typename Y> inline void Scheduler<X, Y>::timeStep() {
	double current_real_time = clock->getRealTime();
	double next_real_time = current_real_time;
	while(true) {
		if(!evt_queue->isEmpty()) {
			cevt = evt_queue->peek();
			next_real_time = cevt->getTime()->getRealTime();
			if(next_real_time != current_real_time) {
				clock = cevt->getTime();
				break;
			}

			cevt = evt_queue->poll();

			if(cevt->hasInput()) {
				input(cevt);
			} else {
				clock = cevt->getTime();
				current = cevt->getModel();
					current->delta(clock, 0);
			}
			if(evt_trace == true) {
				this->eventTrace();
			}
		} else {
			break;
		}
	}

}

template<typename X, typename Y> inline void Scheduler<X, Y>::timeStep(int n) {
	current_time = clock->getRealTime();
	int i = 0;
	while(current_time == clock->getRealTime() && i < n) {
		step();
		i++;
	}
}

template<typename X,typename Y> void Scheduler<X, Y>::step(int n) {
	for(int i = 0; i < n; i++) {
		if(evt_queue->isEmpty()) {
			break;
		} else {
			step();
		}
	}
}

template<typename X, typename Y> void Scheduler<X, Y>::batch() {
	while(!evt_queue->isEmpty()) {
		step();
	}
}

template<typename X, typename Y> inline void Scheduler<X, Y>::setEventTrace(bool evt_trace) {
	this->evt_trace = evt_trace;
}

template<typename X, typename Y> inline bool Scheduler<X, Y>::hasEvent() {
	return evt_queue->isEmpty();
}

template<typename X, typename Y> inline void Scheduler<X, Y>::clearEvents() {
	evt_queue->clear();
}

template<typename X, typename Y> inline void Scheduler<X, Y>::discreteTimeStep() {
}

template<typename X, typename Y> inline void Scheduler<X, Y>::discreteTimeStep(int n) {
}

template<typename X, typename Y> inline void Scheduler<X, Y>::printQueue() {
	std::cout << evt_queue->toString();
	std::cout << std::endl;
}

template<typename X, typename Y> inline Heap<Event<X> *>* Scheduler<X, Y>::getQueue() {
	return evt_queue;
}

template<typename X, typename Y> Scheduler<X, Y>::~Scheduler() {
	delete[] evt_queue;
}
#endif
