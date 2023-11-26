# Repo-de-Tareas-Corregidas
## Lista de cambios realizados:
1. En los archivos list.h y dlist.h, se agregó el siguiente comando al final de la función search (líneas 168-170 y líneas 181-183, respectivamente):

        else if (p->value > val) {
          break;
        }  

2. En el archivo bst.h, en la clase TreeNode, se agregó un "return false;" al final de la función find (línea 76).
3. En el archivo splay.h, se realizaron los siguientes cambios:
    a) La función find de la clase Node, se reescribió de la siguiente manera (líneas 70-80):
   
        template <class T>
        Node<T>* Node<T>::find(T val) {
            if (val < value) {
        return left->find(val);
            } else if (val > value) {
        return right->find(val);
            } else {
        return this;
            }
            return 0;
        }

   b) En la función find de la clase Node (líneas 70-80), se reacomodaron las condiciones if, else if, y else. Además, se agregó un "return 0;" 
   al final de la función:
   
        template <class T>
        Node<T>* Node<T>::find(T val) {
            if (val < value) {
                return left->find(val);
            } else if (val > value) {
                return right->find(val);
            } else {
                return this;
            }
            return 0;
        }

   c) En la función succesor de la clase Node, se agregó la siguiente condición (líneas 89-91):

           if (right == 0) {
        	return 0; 
    	   }

   d) En la función remove de la clase Node, se eliminaron la variable apuntadora root (línea 108) y las siguientes líneas:

   Líneas 109-110:
   
           root = this;
           std::cout << root->value;

   Líneas 136, 172:
   
           old->right = 0;

   Líneas 140, 176:
   
           old->left = 0;

   Línea 143:
   
           return splay(root, left);

   Línea 179:
   
           return splay(root, right);

   e) En la misma función remove, se reescribieron las siguientes líneas:

   Líneas 142-144:
   
           else {
                left = 0;
           }
       
   Línea 149:
   
        return left->remove(val);

   Líneas 179-181:

           else {
                right = 0;
           }

   Línea 186:
   
        return right->remove(val);

   Líneas 145-147, 182-184:

        Node<T>* oldParent = old->parent;
        delete old;
        return oldParent;

   Línea 190:
   
        return 0;
