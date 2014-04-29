#ifndef SYSTEM_H
#define SYSTEM_H
#include "../model/SuperNetwork.hpp"
#include "Press.hpp"
#include "Drill.hpp"
#include "../sim/Scheduler.hpp"



class System : public SuperNetwork<int> {
public:
	System();
	void setScheduler(Scheduler<int, int> *sched);
	void setup();
	void start();
	int delta(Time2D *time, int *input);
	void setInput(int index, int value);
	void addInput(double real_time, int discrete_time, int input);
	~System();
private:
	Scheduler<int, int> *sched;
	Drill *drill;
	Drill *press;
	int output;
	int total_processed;

};
#endif
