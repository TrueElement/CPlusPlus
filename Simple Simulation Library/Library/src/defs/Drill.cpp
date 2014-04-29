#include "../../include/defs/Drill.hpp"

Drill::Drill() {
	this->name = "Generic Drill";
	this->type  = "Drill";
	parts = 0;
	expire = new Time2D(0.0,0);
	process_time = 2;
	time_remaining = 0;
	parts_processed = 0;
}

Drill::Drill(std::string name) {
	this->name = name;
	this->type = "Drill";
	expire = new Time2D(0.0,0);
	parts = 0;
	process_time = 2;
	time_remaining = 0;
	parts_processed = 0;
}

void Drill::timeAdvance(int p, double s) {
	if(p > 0) {
		expire->addTime(s,0);
		throwEvent();
	} else {
		return;
	}
}

void Drill::throwEvent() {
	Event<int> *temp = new Event<int>();
		temp->setModel(this);
		temp->setTime(expire);
	sched->addEvent(temp);
	std::cout << "TE-" << this->name;
	std::cout << ":R-" << expire->getRealTime();
	std::cout << std::endl;
}

int Drill::deltaInternal() {
	int out = lambda();
	if(parts > 0) {
		parts -= 1;
		throwEvent(1);
		timeAdvance(parts, process_time);
	} else {
		throwEvent(1);
		timeAdvance(0, process_time);
	}
	return out;
}

void Drill::deltaExternal(Time2D *time, int *input) {
	double current_time = time->getRealTime();
	time_remaining = expire->getRealTime() - current_time;
	std::cout << "DE-" << this->name << ":TR " << time_remaining << std::endl;
	parts += *input;
	if(time_remaining <= 0) {
		time_remaining = process_time;
	}
	timeAdvance(parts, time_remaining);
}

int Drill::deltaConf(int *input) {
	int out = lambda();
	time_remaining = 0;
	parts += *input;
	if(expire->getRealTime() < process_time) {
		timeAdvance(parts, process_time);
		return out;
	}
	parts -= 1;
	timeAdvance(parts, process_time);
	return out;
}

int Drill::lambda() {
	if(parts > 0) {
		return 1;
	} else {
		return 0;
	}
}

int Drill::delta(Time2D *time, int *input) {
	if(input == 0) {
		if(*time == *expire) {
			deltaInternal();
		} else {
			return 0;
		}
	} else {
		if(*time == *expire) {
			deltaConf(input);
		} else {
			deltaExternal(time, input);
		}
	}
	return 1;
}

int Drill::getProcessedCount() {
	return parts_processed;
}

void Drill::throwEvent(int out) {
	Event<int> *temp;
	Network<int> *con;
	for(unsigned int i = 0; i < connections->size(); i++) {
		con = connections->at(i);
		temp = new Event<int>();
			temp->setModel(con);
			temp->setTime(expire);
			temp->setInput(out);
		sched->addEvent(temp);
	}
}

void Drill::setProcessTime(int process_time) {
	this->process_time = process_time;
}

void Drill::setPartCount(int parts) {
	this->parts = parts;
}

int Drill::getPartCount() {
	return parts;
}

Drill::~Drill() {
}
