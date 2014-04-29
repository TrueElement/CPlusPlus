#ifndef HEAP_H
#define HEAP_H
#include <algorithm>
#include <iostream>
#include <sstream>

template<typename Object> class Comparator {
public:
	int operator() (const Object &lhs, const Object &rhs) const {
		if(lhs < rhs) {
			return -1;
		} else if(lhs == rhs) {
			return 0;
		} else {
			return 1;
		}
	}

	int operator() (Object* const& lhs,Object* const& rhs) const {
		if(*lhs < *rhs) {
			return -1;
		} else if(*lhs == *rhs) {
			return 0;
		} else {
			return 1;
		}
	}
};

template<typename X, typename comparator=Comparator<X> > class Heap {
public:
	Heap() {
		heaparr = new X[10];
		arr_size = 10;
		element_count = 0;
		ss = new std::stringstream();
	}

	Heap(int initial_size) {
		heaparr = new X[initial_size];
		arr_size = initial_size;
		element_count = 0;
		ss = new std::stringstream();
	}

	int size() {
		return element_count;
	}

	int capacity() {
		return arr_size;
	}

	bool isEmpty() {
		return element_count == 0;
	}

	void percolateUp(int index) {
		int parent = index / 2;

		while(index > 0 && (compare(heaparr[index], heaparr[parent]) < 0)) {
			swap(index, parent);
			index = parent;
			parent = index / 2;
		}
	}

	void percolateDown(int index) {
		int left = -1;
		while((2 * index + 1) <= element_count) {
			left = getLeft(index);
			if(left < element_count + 1 && compare(heaparr[left], heaparr[left+1]) < 0) {
				left++;
			}
			if(compare(index, left) < 0) {
				break;
			}
			swap(index, left);
			index = left;
		}
	}

	void enforceMinHeap(int index) {
		int left = getLeft(index);
		int right = getRight(index);
		int smallest = -1;

		int cmpL = 10, cmpR = 10;

		if(left < element_count) {
			cmpL = compare(heaparr[left], heaparr[index]);
		}

		if(cmpL < 0) {
			smallest = left;
		} else {
			smallest = index;
		}

		if(right < element_count) {
			cmpR = compare(heaparr[right], heaparr[smallest]);
		}

		if(cmpR < 0) {
			smallest = right;
		}

		if(smallest != index) {
			swap(index, smallest);
			enforceMinHeap(smallest);
		}
	}

	virtual int compare(X lhs, X rhs) {
		int cmp1 = cmp(lhs, rhs);
		return cmp1;
	}

	X poll() {
		if(isEmpty()) {
			return 0;
		}
		X min = heaparr[0];
		heaparr[0] = heaparr[element_count - 1];
		heaparr[element_count - 1] = 0;
		element_count--;
		enforceMinHeap(0);
		toString();
		return min;
	}

	X peek() {
		if(isEmpty()) {
			return 0;
		}
		return heaparr[0];
	}

	bool add(X  value) {
		if(element_count >= arr_size) {
			increaseArraySize();
		}
		heaparr[element_count] = value;
		percolateUp(element_count);
		element_count += 1;
		toString();
		return true;
	}

	void clear() {
		delete[] heaparr;
		element_count = 0;
		arr_size = 10;
		heaparr = new X[10];
		toString();
	}

	void resort() {
		swap(0, element_count - 1);
		enforceMinHeap(0);
	}

	std::string toString() {
		ss->str("");
		*ss << "{";
		for(int i = 0; i < element_count; i++) {
			if(i != element_count) {
				*ss << "[" << heaparr[i] << "],";
			} else {
				*ss << "[" << heaparr[i] << "]";
			}
		}
		*ss << "}";
		contents = ss->str();
		return ss->str();
	}

	virtual ~Heap() {
		delete[] heaparr;
		delete[] ss;
	}

protected:
	std::stringstream *ss;
	std::string contents;
	comparator cmp;
	X *heaparr;
	int arr_size;
	int element_count;

	int getLeft(int index) {
		return (2 * index) + 1;
	}

	int getRight(int index) {
		return (2 * index) + 2;
	}

	void swap(int x, int y) {
		X temp = heaparr[x];
		heaparr[x] = heaparr[y];
		heaparr[y] = temp;
	}

	void increaseArraySize() {
		X *temp = new X[arr_size + 1];
		std::copy(heaparr, heaparr + arr_size, temp);
		delete[] heaparr;
		heaparr = temp;
		arr_size += 1;
	}
};


#endif
