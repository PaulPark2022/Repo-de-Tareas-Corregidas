/*
 * bst.h
 *
 *  Created on: 05/11/2023
 *      Author: Paul Park A01709885
 */

#ifndef SplayTree_H_
#define SplayTree_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	Node<T>* succesor();
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);
	Node<T>* add(T);
	Node<T>* find(T);
	Node<T>* remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void print_tree(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	Node<T>* splay(Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {}

template <class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri, Node<T> *p)
	: value(val), left(le), right(ri), parent(p) {}

template <class T>
Node<T>* Node<T>::add(T val) {
    if (val < value) { // Si el valor a agregar es menor al valor del nodo
		if (left != 0) { // Si left no es NULL
			return left->add(val); // Recorre izquierda por izquierda
		} else {
			left = new Node<T>(val); // Agrega el valor de una vez
			left->parent = this;
			return left;
		}
	} else { // Si el valor a agregar es mayor al valor del nodo
		if (right != 0) {
			return right->add(val);
		} else {
			right = new Node<T>(val);
			right->parent = this;
			return right;
		}
	}
}

template <class T>
Node<T>* Node<T>::find(T val) {
   if (val == value) {
       return this;
   } else if (val < value) {
       left->find(val);
   } else {
       right->find(val);
   }
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *le, *ri;

	le = left;
	ri = right;

	if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	while (child->left != 0) {
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = 0;
	return child;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
    Node<T> * succ, *old, *root;
    root = this;
    std::cout << root->value;

	if (val < value) { // el valor
		if (left != 0) { // Mientras left no sea nulo
			if (left->value == val) {
				old = left; // nodo a eliminar
				if (old->left != 0 && old->right != 0) { // dos hijos
				    succ = left->succesor();
				    if (succ != 0) {
					    succ->left = old->left;
					    succ->right = old->right;
					    succ->parent = old->parent;
					    if (succ->left)
					        succ->left->parent = succ;
					    if (succ->right)
					        succ->right->parent = succ;
				    }
				    if (old->parent && old->parent->left == old) {
                        old->parent->left = succ;
                    } else if (old->parent && old->parent->right == old) {
                        old->parent->right = succ;
                    }
				    left = succ;
				} else if (old->right != 0) { // solo hijo der
				    old->right->parent = left->parent;
				    left = old->right;
				    old->right = 0;
				} else if (old->left != 0) {
				    old->left->parent = left->parent;
				    left = old->left;
				    old->left = 0;
				}
				delete old;
                return splay(root, left);
			} else {
				left->remove(val); // sigue recorriendo
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				if (old->left != 0 && old->right != 0) {
				    succ = right->succesor();
				    if (succ != 0) {
					    succ->left = old->left;
					    succ->right = old->right;
					    succ->parent = old->parent;
					    if (succ->left)
					        succ->left->parent = succ;
					    if (succ->right)
					        succ->right->parent = succ;
			    	}
			    	if (old->parent && old->parent->left == old) {
                        old->parent->left = succ;
                     } else if (old->parent && old->parent->right == old) {
                       old->parent->right = succ;
                    }
				    right = succ;
				} else if (old->right != 0) {
                    old->right->parent = right->parent; 
                    right = old->right; 
                    old->right = 0;
                } else if (old->left != 0) {
                    old->left->parent = right->parent; 
                    right = old->left; 
                    old->left = 0;
                }
				delete old;
                return splay(root, right);
			} else {
				right->remove(val);
			}
		}
	}
	return root;
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	// enlace de y con el padre de x
	y->parent = x->parent;
	x->parent = y;
	// hace enlace del padre de x a y
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){
		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		}else{
			Node<T>*p = x->parent; // parent
			Node<T>*g = p->parent; // granparent
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree(aux);
	}
	if (right != 0) {
		right->print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
	void splayRoot();
	std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {}

template <class T>
SplayTree<T>::~SplayTree() {
	removeAll();
}

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {
	if (root != 0) {
			Node<T>* added = root->add(val);
			root = root->splay(root,added);
	} else {
		root = new Node<T>(val);
	}
}

template <class T>
void SplayTree<T>::remove(T val) {
    if (root != 0) {
        if (val == root->value) {
            Node<T> *succ = root->succesor();
            if (succ != 0) {
                succ->left = root->left;
                succ->right = root->right;
                succ->parent = 0;
                if (succ->left)
                    succ->left->parent = succ;
                if (succ->right)
                    succ->right->parent = succ;
            }
            delete root;
            root = succ; // Update the root
        } else {
            Node<T>* p = root->remove(val);
            root = root->splay(root, p);
        }
    }
}

template <class T>
void SplayTree<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
void SplayTree<T>::splayRoot() {
    if (root) {
            root = root->splay(root, root);
        }
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root->find(val);
		root = root->splay(root,found);
		return (root->value == val);
	} else {
		return false;
	}
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root->print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif /* SplayTree_H_ */
