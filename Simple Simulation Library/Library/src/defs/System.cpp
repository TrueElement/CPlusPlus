#include "../../include/defs/System.hpp"

System::System() {
	drill = 0;
	press = 0;
	output = 0;
	total_processed = 0;
	sched = 0;
	this->inputarr->push_back(0);
}

void System::setScheduler(Scheduler<int, int> *sched) {
	this->sched = sched;
}

void System::setup() {
	drill = new Drill();
		drill->setProcessTime(2);
		drill->setScheduler(sched);
		drill->setName("Drill");
		drill->setType("Drill");
	press = new Drill();
		press->setProcessTime(1);
		press->setScheduler(sched);
		press->setName("Press");
		press->setType("Press");


	press->addConnection(drill);
	drill->addConnection(this);


}

int System::delta(Time2D *time, int *input) {
	std::cout << "Finished part at: ";
	std::cout << time->getRealTime();
	std::cout << " Press Bin: " << press->getPartCount();
	std::cout << " Drill Bin: " << drill->getPartCount();
	std::cout << std::endl;
	return 0;
}

void System::start() {
	int parts = press->getPartCount();
	press->timeAdvance(parts, 1);
}

void System::setInput(int index, int value) {
	press->setPartCount(value);
}

System::~System() {

}

void System::addInput(double real_time, int discrete_time, int input) {
	Event<int> *temp = new Event<int>(real_time, discrete_time);
		temp->setModel(press);
		temp->setInput(input);
	sched->addEvent(temp);
}
