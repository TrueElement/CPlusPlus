#ifndef COUPLING_H
#define COUPLING_H
template<typename X> class Network;

template<typename X> class Coupling {
public:
	Coupling();
	Coupling(Network<X> *src, Network<X> *dest);
	void translate();
	void setSource(Network<X>* src);
	void setDestination(Network<X>* dest);
	void setIndex(int src_index, int dest_index);
	void setSourceIndex(int src_index);
	void setDestIndex(int dest_index);
	~Coupling();
private:
	Network<X> *src, *dest;
	int src_index, dest_index;
};

template<typename X> Coupling<X>::Coupling() {
	src = 0;
	dest = 0;
	src_index = 0;
	dest_index = 0;
}

template<typename X> Coupling<X>::Coupling(Network<X>* src, Network<X>* dest) {
	this->src = src;
	this->dest = dest;
	src_index = 0;
	dest_index = 0;
}

template<typename X> void Coupling<X>::translate() {

}

template<typename X> void Coupling<X>::setSource(Network<X>* src) {
	this->src = src;
}

template<typename X> void Coupling<X>::setDestination(Network<X>* dest) {
	this->dest = dest;
}



template<typename X> void Coupling<X>::setIndex(int src_index, int dest_index) {
	this->src_index = src_index;
	this->dest_index = dest_index;
}

template<typename X> void Coupling<X>::setSourceIndex(int src_index) {
	this->src_index = src_index;
}

template<typename X> void Coupling<X>::setDestIndex(int dest_index) {
	this->dest_index = dest_index;
}

template<typename X> Coupling<X>::~Coupling() {
}

#endif

