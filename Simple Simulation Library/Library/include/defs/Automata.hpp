#ifndef AUTOMATA_H
#define AUTOMATA_H
#include <sstream>
#include <iostream>
#include "../model/SuperNetwork.hpp"
#include "Cell.hpp"
class Automata : public SuperNetwork<int> {
public:
	Automata();
	Automata(int cell_count);
	void setCellCount(int cell_count);
	void setCell(int index, int value);
	void printCellRelations();
	void setup();
	void cellString();
	void step();
	void step(int n);
	void print();
	void output();
	int getOutput();
	void start();
	void computeChildren();
	~Automata();
private:
	int cell_count;
	std::vector<Cell *> *cells;
	std::string last_line;
	std::string line;
};
#endif
