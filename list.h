#ifndef LIST_H_
#define LIST_H_

#include <string>
#include <sstream>

template <class T> class List;
template <class T> class ListIterator;

template <class T>
class Link {
private:
	Link(T);
	Link(T, Link<T>*);
	Link(const Link<T>&);

	T	    value;
	Link<T> *next;

	friend class List<T>;
	friend class ListIterator<T>;
};

template <class T>
Link<T>::Link(T val) : value(val), next(0) {} 

template <class T>
Link<T>::Link(T val, Link* nxt) : value(val), next(nxt) {}

template <class T>
Link<T>::Link(const Link<T> &source) : value(source.value), next(source.next) {}

template <class T>
class List {
public:
	List();
	List(const List<T>&) ;
	~List();
	
	void addFirst(T) ;
	void insertion(T);
	void clear();
	std::string toString() const;
	bool empty() const;
	T    search(int) const;
	void update(int,int);
	void deleteAt(int);
private:
	Link<T> *head;
	int 	size;

	friend class ListIterator<T>;
};

template <class T>
List<T>::List() : head(0), size(0) { 
}

template <class T>
List<T>::~List() {
	clear();
}

template <class T>
bool List<T>::empty() const {
	return (head == 0);
}

template <class T>
void List<T>::addFirst(T val)  {
	Link<T> *newLink;

	newLink = new Link<T>(val); 

	newLink->next = head; 
	head = newLink; 
	size++;
}

template <class T> 
void List<T>::insertion(T val)  {
	Link<T> *newLink, *p;

	newLink = new Link<T>(val); 
	
	if (empty()) { 
		addFirst(val);
		return;
	}

	p = head; // 
	while (p->next != 0) { 
		p = p->next;
	}

	newLink->next = 0;
	p->next = newLink; 
	size++;
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next; 
		delete p;
		p = q; 
	}
	head = 0;
	size = 0;
}

template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

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
List<T>::List(const List<T> &source)  {
	Link<T> *p, *q;

	if (source.empty()) {
		size = 0;
		head = 0;
	} else {
		p = source.head; 
		head = new Link<T>(p->value); 
		q = head; 

		p = p->next;
		while(p != 0) {
			q->next = new Link<T>(p->value); 
			p = p->next;
			q = q->next;
		}
		size = source.size;
	}
}

template <class T>
T List<T>::search(int val) const {
	int pos;
	Link<T> *p;

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
void List<T>::update(int pos, int newVal) {
	Link<T> *p;
	
    int index = 0;
	p = head;
	
	while (index < pos) { 
		p = p->next;
		index++;
	}

	p->value = newVal;
}

template <class T>
void List<T>::deleteAt(int pos) {
    Link<T> *p;
    Link<T> *q = 0;
    
    int index = 0;
    p = head;
    
    while (index < pos) {
        q = p;
        p = p->next;
        index++;
    }
    
    if(q == 0) {
        head = head->next;
        delete p;
        size--;
    } else if (p != 0) {
        q->next = p->next;
        delete p;
        size--;
    }
}

#endif /* LIST_H_ */