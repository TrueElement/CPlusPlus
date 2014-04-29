#ifndef DRILL_H
#define DRILL_H
#include <iostream>
#include "../model/Network.hpp"
class Drill : public Network<int> {
public:
	Drill();
	Drill(std::string name);
	void throwEvent();
	void throwEvent(int out);
	void setProcessTime(int process_time);
	void setPartCount(int parts);
	void timeAdvance(int p, double s);
	int deltaInternal();
	void deltaExternal(Time2D *time, int *input);
	int deltaConf(int *input);
	int delta(Time2D *time, int *input);
	int lambda();
	int getProcessedCount();
	int getPartCount();
	~Drill();
private:
	int parts;
	int parts_processed;
	double time_remaining;
	int process_time;
};
#endif
