#include "../../include/sim/Time2D.hpp"
#include <iostream>
/*
 * Class Definition Time2D
 */

Time2D::Time2D() {
	real_time = 0.0;
	discrete_time = 0;
}

Time2D::Time2D(double real_time, int discrete_time) {
	this->real_time = real_time;
	this->discrete_time = discrete_time;
}

void Time2D::setRealTime(double real_time) {
	this->real_time = real_time;
}



double Time2D::getRealTime() {
	return real_time;
}

void Time2D::setDiscreteTime(int discrete_time) {
	this->discrete_time = discrete_time;
}

int Time2D::getDiscreteTime() {
	return discrete_time;
}

bool Time2D::operator <(const Time2D& rhs) const {
	if(real_time == rhs.real_time) {
		if(discrete_time < rhs.discrete_time) {
			return true;
		} else {
			return false;
		}
	} else {
		if(real_time < rhs.real_time) {
			return true;
		} else {
			return false;
		}
	}
}

bool Time2D::operator ==(const Time2D& rhs) const {
	if(rhs.real_time == real_time) {
		if(rhs.discrete_time == discrete_time) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

Time2D * Time2D::operator +(Time2D* rhs) {
	if(real_time == rhs->getRealTime()) {
		discrete_time += rhs->getDiscreteTime();
	} else {
		real_time = rhs->getRealTime();
		discrete_time = 0;
	}
	return this;
}

void Time2D::addTime(double real_time, double discrete_time) {
	if(real_time == this->real_time) {
		if(discrete_time == 0) {
			this->real_time += real_time;
		} else {
			this->discrete_time += discrete_time;
		}
	} else {
		this->discrete_time = 0;
		this->real_time += real_time;
	}
}

std::string Time2D::toString() {
	std::stringstream ss;
	ss << real_time;
	ss << ":";
	ss << discrete_time;
	return ss.str();
}



Time2D::~Time2D() {
}


