#ifndef CELL_H
#define CELL_H
#include "../model/Network.hpp"

class Cell : public Network<int> {
public:
	Cell() {
		left = 0;
		right = 0;
		value = 0;
		this->type = "Cell";
		cell_num = 0;
		val_changed = false;
		last_val = 0;
	}

	Cell(Cell *left, Cell *right) {
		this->left = left;
		this->right = right;
		this->type = "Cell";
		value = 0;
		cell_num = 0;
		val_changed = false;
		last_val = 0;
	}

	void setCellNum(int cell_num) {
		this->cell_num = cell_num;
	}

	void throwEvent() {
		double real_time = last->getRealTime();
		Time2D *n_time = new Time2D();
			n_time->setRealTime(real_time + 1);
			n_time->setDiscreteTime(0);

		if(left != 0) {
			Event<int> *l_evt = new Event<int>();
				l_evt->setModel(left);
				l_evt->setTime(n_time);
			sched->addEvent(l_evt);
		}

		if(right != 0) {
			Event<int> *r_evt = new Event<int>();
				r_evt->setModel(right);
				r_evt->setTime(n_time);
			sched->addEvent(r_evt);
		}


	}

	void setLeft(Cell *left) {
		this->left = left;
	}

	void setRight(Cell *right) {
		this->right = right;
	}

	Cell * getLeft() {
		return left;
	}

	Cell *getRight() {
		return right;
	}

	void setValue(int value) {
		last_val = value;
		this->value = value;
		this->last = this->expire;
		this->val_changed = true;
	}

	int getValue() {
		return value;
	}

	int getLastValue() {
		return last_val;
	}

	int delta(Time2D *time, int *input) {
		int cur_val = value;
		this->last = this->expire;
		this->expire = time;
		compute();
		if(cur_val != value) {
			this->throwEvent();
		}
		//this->throwEvent();
		return value;
	}

	void compute() {
		int lval = 0, rval = 0;
		int cur_val = value;
		val_changed = false;
		if(left == 0) {
			lval = 0;
		} else {
			lval = left->getLastValue();
		}

		if(right == 0) {
			rval = 0;
		} else {
			rval = right->getLastValue();
		}

		if(value == 0) {
			if(lval == 0 && rval == 0) {
				value = 0;
			} else if(lval == 0 && rval == 1) {
				value = 1;
			} else if(lval == 1 && rval == 0) {
				value = 0;
			} else if(lval == 1 && rval == 1) {
				value = 1;
			}
		} else if(value == 1) {
			if(lval == 0 && rval == 0) {
				value = 1;
			} else if(lval == 0 && rval == 1) {
				value = 1;
			} else if(lval == 1 && rval == 0) {
				value = 1;
			} else if(lval == 1 && rval == 1) {
				value = 0;
			}
		}
		if(cur_val != value) {
			val_changed = true;
		}
	}

	bool valChanged() {
		return val_changed;
	}

	void updateLastVal() {
		last_val = value;
	}
private:
	Cell *left, *right;
	bool val_changed;
	int value;
	int last_val;
	int cell_num;
};
#endif
