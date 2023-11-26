# Repo-de-Tareas-Corregidas
## Lista de cambios realizados:
1. En los archivos list.h y dlist.h, se agregó el siguiente comando al final de la función search (líneas 168-170 y líneas 181-183, respectivamente):

  else if (p->value > val) {
    break;
  }  

2. En el archivo bst.h, en la clase TreeNode, se agregó un "return false;" al final de la función find (línea 76).
3. En el archivo splay.h, se realizaron los siguientes cambios:
    a) La función find de la clase Node, se reescribió de la siguiente manera (líneas 70-79):
   
        template <class T>
        Node<T>* Node<T>::find(T val) {
          if (val < value) {
            return left->find(val);
          } else if (val > value) {
            return right->find(val);
          } else {
            return this;
          }
        }

   b) En la función remove de la clase Node, se eliminó la siguiente secuencia de código:
       

   
