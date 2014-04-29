#ifndef TIME
#define TIME
#include <sstream>

class Time2D {
public:
	Time2D();
	Time2D(double real_time, int discrete_time);
	void setRealTime(double real_time);
	double getRealTime();
	void setDiscreteTime(int discrete_time);
	int getDiscreteTime();
	bool operator <(const Time2D&rhs) const;
	bool operator ==(const Time2D& rhs) const;
	Time2D * operator +(Time2D *rhs);
	void addTime(double real_time, double discrete_time);
	std::string toString();
	~Time2D();
private:
	double real_time;
	int discrete_time;
};

class TimeCompare {
public:
	bool operator() (Time2D* const& lhs, Time2D* const& rhs) {
		if(lhs->getRealTime() == rhs->getRealTime()) {
			if(lhs->getDiscreteTime() > rhs->getDiscreteTime()) {
				return true;
			} else {
				return false;
			}
		} else {
			if(lhs->getRealTime() > rhs->getRealTime()) {
				return true;
			} else {
				return false;
			}
		}
	}
private:
};
#endif
