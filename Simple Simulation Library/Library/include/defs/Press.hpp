#ifndef PRESS_H
#define PRESS_H
#include <iostream>
#include "../model/Network.hpp"
class Press : public Network<int> {
public:
	Press();
	Press(std::string name);
	void timeAdvance(int p, double s);
	int deltaInternal();
	void deltaExternal(Time2D *time, int *input);
	int deltaConf(int *input);
	//void delta(Time2D *time, int *input);
	int lambda();
	int getProcessedCount();
	~Press();
private:
	int parts;
	int parts_processed;
	double time_remaining;
	int process_time;
};
#endif

