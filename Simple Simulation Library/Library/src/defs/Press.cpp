#include "../../include/defs/Press.hpp"

Press::Press() {
	this->name = "Generic Press";
	this->type  = "Press";
	parts = 0;
	expire = new Time2D(0.0,0);
	process_time = 1;
	time_remaining = 0;
	parts_processed = 0;
}

Press::Press(std::string name) {
	this->name = name;
	this->type = "Press";
	expire = new Time2D(0.0,0);
	parts = 0;
	process_time = 1;
	time_remaining = 0;
	parts_processed = 0;
}

void Press::timeAdvance(int p, double s) {
	if(p > 0) {
		expire->setRealTime(s);
	} else {
		expire->setRealTime(1000000000);
	}
}

int Press::deltaInternal() {
	if(parts > 0) {
		parts -= 1;
		parts_processed += 1;
		timeAdvance(parts, process_time);
		return 1;
	} else {
		timeAdvance(0, process_time);
		return 0;
	}
}

void Press::deltaExternal(Time2D *time, int *input) {
	time_remaining = expire->getRealTime() - time->getRealTime();
	parts += *input;
	timeAdvance(parts, time->getRealTime() + time_remaining);
}

int Press::deltaConf(int *input) {
	time_remaining = 0;
	parts += *input;
	parts -= 1;
	parts_processed += 1;
	timeAdvance(parts, process_time);
	return 1;
}

int Press::lambda() {
	if(parts > 0) {
		std::cout << "Press " << expire->toString();
		std::cout << " out: 1" << std::endl;
		this->translateOutput();
		return 1;
	} else {
		std::cout << "Press " << expire->toString();
		std::cout << " out: 0" << std::endl;
		this->translateOutput();
		return 0;
	}
}

int Press::getProcessedCount() {
	return parts_processed;
}

Press::~Press() {
}
