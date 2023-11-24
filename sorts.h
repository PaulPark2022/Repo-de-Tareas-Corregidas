/*
 * sorts.h
 *
 *  Created on: 31/08/2023
 *      Author: Paul Park A01709885
 */

#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <string>
#include <list>

using namespace std;

template <class T>
class Sorts {
private:
	void swap(std::vector<T>&, int, int);
	void copyArray(std::vector<T>&, std::vector<T>&, int, int);
	void mergeArray(std::vector<T>&, std::vector<T>&, int, int, int);
	void mergeSplit(std::vector<T>&, std::vector<T>&, int, int);
public:
	std::vector<T> ordenaBurbuja(std::vector<T>&);
	std::vector<T> ordenaSeleccion(std::vector<T>&);
	std::vector<T> ordenaMerge(std::vector<T>&);
	int busqSecuencial(std::vector<T>&, int);
	int busqBinaria(std::vector<T>&, int);
};

template <class T>
void Sorts<T>::swap(std::vector<T> &v, int i, int j) {
	T aux = v[i];
	v[i] = v[j];
	v[j] = aux;
}

template <class T>
std::vector<T> Sorts<T>::ordenaBurbuja(std::vector<T> &source) {
	for (int j = source.size() - 1; j > 0; j--){
		for(int i = 0; i < j; i++){
			if (source[i] > source[i+1]){
				swap(source, i, i+1);
			}
		}
	}
	return source;
}

template <class T>
std::vector<T> Sorts<T>::ordenaSeleccion(std::vector<T> &source) {
	int pos;

	for (int j = source.size() - 1; j > 0; j--){
		pos = 0;
		for (int i = 1; i <= j; i++){
			if (source[i] > source[pos]){
				pos = i;
			}
		} 
		if (pos != j) {
			swap(source, j, pos);
		}
	}
	return source;
}

template <class T>
void Sorts<T>::copyArray(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	for (int i = low; i <= high; i++) {
		A[i] = B[i];
	}
}

template <class T>
void Sorts<T>::mergeArray(std::vector<T> &A, std::vector<T> &B, int low, int mid, int high) {
	int i, j, k;

	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid && j <= high) {
		if (A[i] < A[j]) {
			B[k] = A[i];
			i++;
		} else {
			B[k] = A[j];
			j++;
		}
		k++;
	}
	if (i > mid) {
		for (; j <= high; j++) {
			B[k++] = A[j];
		}
	} else {
		for (; i <= mid; i++) {
			B[k++] = A[i];
		}
	}
}

template <class T>
void Sorts<T>::mergeSplit(std::vector<T> &A, std::vector<T> &B, int low, int high) {
	int mid;

	if ( (high - low) < 1 ) {
		return;
	}
	mid = (high + low) / 2;
	mergeSplit(A, B, low, mid);
	mergeSplit(A, B, mid + 1, high);
	mergeArray(A, B, low, mid, high);
	copyArray(A, B, low, high);
}

template <class T>
std::vector<T> Sorts<T>::ordenaMerge(std::vector<T> &source) {
	std::vector<T> v(source);
	std::vector<T> tmp(v.size());

	mergeSplit(v, tmp, 0, v.size() - 1);
	copyArray(source, v, 0, v.size() - 1);
	return source;
}

template <class T> 
int Sorts<T>::busqSecuencial(std::vector<T> &v, int dato){
	for (int i = 0; i < v.size(); i++){
		if (dato == v[i]) {
			return i;
		} 	
	}
	return -1;
}


template <class T>
int Sorts<T>::busqBinaria(std::vector<T> &v, int dato){
	int i = 0;
	int low = 0;
	int mid;
	int high = v.size() - 1;

	while (i < high) {
		mid = (high + low) / 2;
		if (dato == v[mid]) {
			return mid;
		} else if (dato < v[mid]) {
			high = mid - 1;
			i++;
		} else if (dato > v[mid]) {
			low = mid + 1;
			i++;
		}
	}
	return -1;
}

#endif /* SORTS_H_ */