#ifndef INPUT_H
#define INPUT_H
#include "Pair.hpp"

template<typename X, typename Y, typename Z> class Input : public Pair<X, Y> {
public:
	Input() {
		z = 0;
	}

	Input(X *x, Y *y, Z *z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void setZ(Z *z) {
		this->z = z;
	}

	Z * getZ() {
		return this->z;
	}

	virtual ~Input() {

	}
protected:
	Z *z;
};

template <typename X, typename Z> class AtomicInput : public Input<X, Time2D, Z> {
public:
	AtomicInput() {
		this->mod = 0;
		this->time = 0;
	}

	AtomicInput(Atomic<X> *mod, Time2D *time, Z *input) {
		this->mod = mod;
		this->time = time;
		this->z = input;
	}

	void setModel(Atomic<X> *mod) {
		this->mod = mod;
	}

	Atomic<X> * getModel() {
		return this->mod;
	}

	void setTime(Time2D *time) {
		this->time = time;
	}

	Time2D * getTime() {
		return this->time;
	}

	void setInput(Z *input) {
		this->z = input;
	}

	Z * getInput() {
		return this->getZ();
	}

	~AtomicInput() {

	}
protected:
	Atomic<X> *mod;
	Time2D *time;
};

template<typename X, typename Z> class AtomicInputCompare {
public:
	int operator() (AtomicInput<X,Z>* const& lhs, AtomicInput<X,Z>* const& rhs) {
		Time2D *lhs_time = lhs->getTime();
		Time2D *rhs_time = rhs->getTime();

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
#endif
