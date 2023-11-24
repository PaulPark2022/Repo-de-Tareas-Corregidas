/*
 * bst.h
 *
 *  Created on: 08/10/2023
 *      Author: Paul Park A01709885
 */

#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>

using namespace std;

template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

	TreeNode<T>* succesor();

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);
	void add(T);
	bool find(T);
	void remove(T);
	void removeChilds();
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
	void levelorder(std::stringstream&, TreeNode*, int) const;
	void ancestors(std::stringstream&, T) const;
	
	friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0) {}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) 
	: value(val), left(le), right(ri) {}

template <class T>
void TreeNode<T>::add(T val) {
	if (val < value) { // Si el valor a agregar es menor al valor del nodo
		if (left != 0) { // Si left no es NULL
			left->add(val); // Recorre izquierda por izquierda
		} else {
			left = new TreeNode<T>(val); // Agrega el valor de una vez
		}
	} else { // Si el valor a agregar es mayor al valor del nodo
		if (right != 0) {
			right->add(val);
		} else {
			right = new TreeNode<T>(val);
		}
	}
}

template <class T>
bool TreeNode<T>::find(T val) {
	if (val == value) {
		return true;
	} else if (val < value) {
		return (left != 0 && left->find(val));
	} else if (val > value) {
		return (right != 0 && right->find(val));
	}
	
	return false;
}

template <class T>
TreeNode<T>* TreeNode<T>::succesor() {
	TreeNode<T> *le, *ri;

	le = left;
	ri = right;

	if (left == 0) { // Si no hay sucesor para left
		if (right != 0) {
			right = 0;
		}
		return ri;
	}

	if (left->right == 0) { // Si no hay sucesor
		left = left->left;
		le->left = 0;
		return le;
	}

	TreeNode<T> *parent, *child;
	parent = left;
	child = left->right;
	while (child->right != 0) {
		parent = child;
		child = child->right;
	}
	parent->right = child->left;
	child->left = 0;
	return child;
}

template <class T>
void TreeNode<T>::remove(T val) {
	TreeNode<T> * succ, *old;

	if (val < value) { // el valor
		if (left != 0) { // Mientras left no sea nulo
			if (left->value == val) {
				old = left; // nodo a eliminar
				succ = left->succesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				left = succ;
				delete old;
			} else {
				left->remove(val); // sigue recorriendo
			}
		}
	} else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				old = right;
				succ = right->succesor();
				if (succ != 0) {
					succ->left = old->left;
					succ->right = old->right;
				}
				right = succ;
				delete old;
			} else {
				right->remove(val);
			}
		}
	}
}

template <class T>
void TreeNode<T>::removeChilds() {
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
void TreeNode<T>::inorder(std::stringstream &aux) const {
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
void TreeNode<T>::preorder(std::stringstream &aux) const {
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
void TreeNode<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
		aux << " ";
	}
	if (right != 0) {
		right->postorder(aux);
		aux << " ";
	}
	aux << value;
}

template <class T>
void TreeNode<T>::levelorder(std::stringstream &aux, TreeNode* root, int level) const {
    if (root == 0) {
        return;
    }
    if (level == 1) {
        if (aux.tellp() != 1) {
			aux << " ";
		}
        aux << root->value;
    } else if (level > 1) {
        if (root->left != 0) {
            levelorder(aux, root->left, level - 1);
        }
        if (root->right != 0) {
            levelorder(aux, root->right, level - 1);
        }
    }
}

template <class T>
void TreeNode<T>::ancestors(std::stringstream &aux, T val) const {
    if (value != val) {
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << value;

        if (val < value && left != 0) {
            left->ancestors(aux, val);
        }
        if (val > value && right != 0) {
            right->ancestors(aux, val);
        }
    }
}
    
template <class T>
class BST {
private:
	TreeNode<T> *root;

public:
	BST();
	~BST();
	bool empty() const;
	void add(T);
	bool find(T) const;
	void remove(T);
	void removeAll();
	std::string visit() const;
	std::string inorder() const;
	std::string preorder() const;
	std::string postorder() const;
	std::string levelorder() const;
	int obtainHeight(TreeNode<T>*) const;
	int height() const;
	std::string ancestors(T) const;
	int obtainLevel(TreeNode<T>*, T, int) const;
	int whatlevelamI(T) const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
	removeAll();
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

template<class T>
void BST<T>::add(T val) {
	if (root != 0) { // Mientras root no apunte a NULL
		if (!root->find(val)) {
			root->add(val); // Llamar función para agregar de root
		}
	} else {
		root = new TreeNode<T>(val); // Si no hay raíz, crear raíz
	}
}

template <class T>
void BST<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			TreeNode<T> *succ = root->succesor();
			if (succ != 0) {
				succ->left = root->left;
				succ->right = root->right;
			}
			delete root;
			root = succ;
		} else {
			root->remove(val);
		}
	}
}

// 0(log (n)) == Divide la mitad por la mitad por la mitad
template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool BST<T>::find(T val) const {
	if (root != 0) {
		return root->find(val);
	} else {
		return false;
	}
}

template <class T>
int BST<T>::obtainHeight(TreeNode<T> *node) const {
    if (node == 0){
        return 0;
    } else {
        int leftHeight = obtainHeight(node->left);
        int rightHeight = obtainHeight(node->right);
        
        return 1 + std::max(leftHeight, rightHeight);
    }
}

template <class T>
int BST<T>::height() const{
    return obtainHeight(root);
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
	if (!find(val)) {
		return "[]";
	}
    aux << "[";
    root->ancestors(aux, val);
    aux << "]";
    return aux.str();
}

template <class T>
int BST<T>::obtainLevel(TreeNode<T>* node, T val, int level) const {
    if (node == 0) {
        return 0;
    }

    if (val == node->value) {
        return level;
    } else if (val < node->value) {
        return obtainLevel(node->left, val, level + 1);
    } else {
        return obtainLevel(node->right, val, level + 1);
    }
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    return obtainLevel(root, val, 1);
}

template <class T>
std::string BST<T>::visit() const {
	std::stringstream aux;
	
	aux << preorder() << "\n";
	aux << inorder() << "\n";
	aux << postorder() << "\n";	
	aux << levelorder();

	return aux.str();
}

template <class T>
std::string BST<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
std::string BST<T>::levelorder() const {
	std::stringstream aux;
	int h = height();

	aux << "[";
	if (!empty()) {
		for (int i = 1; i <= h; i++) {
        	root->levelorder(aux, root, i);
    	}
	}
	aux << "]";
	return aux.str();
}

#endif /* BST_H_ */
