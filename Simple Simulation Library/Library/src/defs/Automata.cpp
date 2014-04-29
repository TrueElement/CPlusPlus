#include "../../include/defs/Automata.hpp"

Automata::Automata() {
	cell_count = 0;
	cells = new std::vector<Cell *>();
	sched = 0;
}

Automata::Automata(int cell_count) {
	this->cell_count = cell_count;
	cells = new std::vector<Cell *>();
	sched = 0;
}

void Automata::setCell(int index, int value) {
	cells->at(index)->setValue(value);
}

void Automata::setup() {
	Cell *temp;
	std::stringstream ss1;
	for(int i = 0; i < cell_count + 1; i++) {
		temp = new Cell();
		temp->setScheduler(sched);
		temp->setValue(0);
		temp->setExpireTime(-1.0,0);
		temp->setCellNum(i);
		ss1 << i;
		temp->setName(ss1.str());
		ss1.str("");
		cells->push_back(temp);
	}

	Cell *left;
	Cell *right;
	for(int i = 0; i < cell_count + 1; i++) {
		temp = cells->at(i);
		if(i == 0) {
			right = cells->at(i);
			temp->setRight(right);
			continue;
		}
		if(i == cell_count) {
			left = cells->at(i - 1);
			temp->setLeft(left);
			break;
		}
		left = cells->at(i - 1);
		right = cells->at(i + 1);
		temp->setLeft(left);
		temp->setRight(right);
	}
}

void Automata::step() {
	last_line = line;
	output();
	computeChildren();
	if(last_line.compare(line) == 0) {
		std::cout << "Recurring Output" << std::endl;
	}
}

void Automata::step(int n) {
	for(int i = 0; i < n; i++) {
		step();
	}
}

void Automata::print() {
	std::cout << ss->str() << std::endl;
}

void Automata::setCellCount(int cell_count) {
	this->cell_count = cell_count;
}

void Automata::cellString() {
	std::stringstream ss1;
	Cell *temp = 0;
	unsigned int i = 0;
	int temp_val = 0;
	for(i = 0; i < cells->size(); i++) {
		temp = cells->at(i);
		temp_val = temp->getValue();
		if(temp_val == 0) {
			ss1 << " ";
		} else if(temp_val == 1) {
			ss1 << "1";
		}
	}
	ss1 << " ";
	line = ss1.str();
	*ss << line;
	*ss << std::endl;
}

void Automata::output() {
	cellString();
	std::cout << ss->str();
}

int Automata::getOutput() {
	return 0;
}

void Automata::start() {
	unsigned int i = 0;
	Cell *temp;
	for(i = 0; i < cells->size(); i++) {
		temp = cells->at(i);
		if(temp->getValue() == 1) {
			temp->throwEvent();
		}
	}
}



void Automata::printCellRelations() {
	unsigned int i = 0;
	std::stringstream ss1;
	Cell *temp;
	Cell *temp_l;
	Cell *temp_r;
	for(i = 0; i < cells->size(); i++) {
		temp = cells->at(i);
		temp_l = temp->getLeft();
		temp_r = temp->getRight();
		if(temp_l == 0) {
			ss1 << "[null:";
		} else {
			ss1 << "[";
			ss1 << temp_l->getName();
			ss1 << ":";
		}
		ss1 << temp->getName();
		ss1 << ":";
		if(temp_r == 0) {
			ss1 << "null]";
		} else {
			ss1 << temp_r->getName();
			ss1 << "]";
		}
		ss1 << std::endl;
	}
	ss1 << std::endl;
	std::cout << ss1.str();
}

void Automata::computeChildren() {
	Cell *temp;
	for(unsigned int i = 0; i < cells->size(); i++) {
		temp = cells->at(i);
		temp->compute();
	}

	temp = 0;
	for(unsigned int i = 0; i < cells->size(); i++) {
		temp = cells->at(i);
		temp->updateLastVal();
	}
}

Automata::~Automata() {
	delete[] cells;
}


