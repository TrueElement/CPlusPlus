#ifndef SYSTEMCLIENT_H
#define SYSTEMCLIENT_H
#include "../sim/Client.hpp"
#include "../model/Network.hpp"

class SystemClient : public Client<int, int> {
public:
	SystemClient();
	void input();
	void inputn();
	void output();
	void print();
	~SystemClient();
private:
	int parts, discrete_time;
	double real_time;
	Time2D *time;
};
#endif

