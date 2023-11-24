/*
 * funciones.h
 *
 *  Created on: 21/08/2023
 *      Author: Paul Park A01709885
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

using namespace std;

class Funciones {
public:
	long sumaIterativa(int);
	long sumaRecursiva(int);
	long sumaDirecta(int);
};

long Funciones::sumaIterativa(int n) {
    long acum = 0;
	if (n < 0) {
		return -1;
	} else {
		for (int i = 0; i <= n; i++) {
			acum += i;
		}
		return acum;
	} 
}

long Funciones::sumaRecursiva(int n) {
	if (n < 0) {
		return -1;
	} else if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else {
		return n + sumaRecursiva(n - 1);
	}
}

long Funciones::sumaDirecta(int n) {
	if (n < 0) {
		return -1;
	} else if (n == 0) {
		return 0;
	} else if (n == 1) {
		return 1;
	} else {
		return (n * (n + 1)) / 2;
	}
}

#endif /* FUNCIONES_H_ */