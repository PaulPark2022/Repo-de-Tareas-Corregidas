/*
 * dlist.h
 *
 *  Created on: 26/09/2023
 *      Author: Paul Park
 */

#ifndef DLIST_H_
#define DLIST_H_

#include <string>
#include <sstream>

template <class T> class DList;
template <class T> class DListIterator;

template <class T>
class DLink {
private:
	DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T>&);

	T	    value;
	DLink<T> *previous;
	DLink<T> *next;

	friend class DList<T>;
	friend class DListIterator<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}

template <class T>
DLink<T>::DLink(T val, DLink *prev, DLink* nxt) : value(val), previous(prev), next(nxt) {}

template <class T>
DLink<T>::DLink(const DLink<T> &source) : value(source.value), previous(source.previous), next(source.next) {}

template <class T>
class DList {
public:
	DList();
	DList(const DList<T>&);
	~DList();

	void insertion(T);
	bool empty() const;
	void clear();
	std::string toStringForward() const;
	std::string toStringBackward() const;
	T    search(int) const;
	void update(int,int);
	void deleteAt(int);
private:
	DLink<T> *head;
	DLink<T> *tail;
	int 	 size;

	friend class DListIterator<T>;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
DList<T>::~DList() {
	clear();
}

template <class T>
bool DList<T>::empty() const {
	return (head == 0 && tail == 0);
}

template <class T>
void DList<T>::insertion(T val)  {
	DLink<T> *newLink;

	newLink = new DLink<T>(val);

	if (empty()) {
		head = newLink;
		tail = newLink;
	} else {
		tail->next = newLink;
		newLink->previous = tail;
		tail = newLink;
	}
	size++;
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
std::string DList<T>::toStringForward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string DList<T>::toStringBackward() const {
	std::stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}

template <class T>
DList<T>::DList(const DList<T> &source)  {
	DLink<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
		tail = 0;
	} else {
		p = source.head;
		head = new DLink<T>(p->value);
		q = head;

		p = p->next;
		while(p != 0) {
			q->next = new DLink<T>(p->value, q, 0);
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
T DList<T>::search(int val) const {
	int pos;
	DLink<T> *p;

	p = head;
	pos = 0;
	
	while (p->value < val) {
	    p = p->next;
		pos++;
		if (p->value == val) {
		    return pos;
		} else if (p->value > val) {
		    break;
		}
	}
	
	return -1;
}

template <class T>
void DList<T>::update(int pos, int newVal) {
	DLink<T> *p;
	
    int index = 0;
	p = head;
	
	while (index < pos) { 
		p = p->next;
		index++;
	}

	p->value = newVal;
}

template <class T>
void DList<T>::deleteAt(int pos) {
    DLink<T> *p;
    DLink<T> *q = 0;
    
    int index = 0;
    p = head;
    
    while (index < pos) {
        q = p;
        p = p->next;
        index++;
    }
    
    if (p != 0) {
		if (p->previous == 0) {
			head = p->next;
			p->next->previous = 0;
		} else {
			p->previous->next = p->next;
			if (p->next != 0) {
				p->next->previous = p->previous;
			}
		}
		size--;
	}
}

#endif /* DLIST_H_ */
