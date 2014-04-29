#ifndef PAIR
#define PAIR
template<typename X, typename Y> class Pair {
public:
	Pair() {
		x = 0;
		y = 0;
	}
	Pair(X *x, Y *y) {
		this->x = x;
		this->y = y;
	}

	void setX(X *x) {
		this->x = x;
	}

	X getX() {
		return this->x;
	}

	void setY(Y *y) {
		this->y = y;
	}

	Y getY() {
		return this->y;
	}

	bool operator <(Pair *rhs) {
		return *x < *y;
	}

	virtual ~Pair() {

	}

protected:
	X *x;
	Y *y;
};
#endif
