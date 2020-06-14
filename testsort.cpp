/*
Autor: Jefferson Miguel Flores Herrera								
Repositorio: https://github.com/jfloreshe/ADA/blob/master/practica5.cpp
https://github.com/jfloreshe/ADA/blob/master/	
branch: master  													
Curso: Analisis y Diseno de Algoritmos Laboratorio A
*/

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <stdlib.h>
#include <vector>
#define INF 100

void merge_sort(long*& array, const int indiceP,const int indiceR);
void intercala(long*& array, const int indiceP,const int indiceQ, const int indiceR);
////array and vector handlers///
long* generate_array(const int);
void mostrar_array(long* array, const int);

template <typename T>
T* copy_array(T*& arrayA, T*& arrayB, int size);
/////////QSORT from stdlib//////////
int compare(const void*a, const void*b){return (*(int*)a - *(int*)b);}
int compare2(const void*a, const void*b){return (*(int*)b - *(int*)a);}

////////////MAIN//////////////
int main(){
	srand (time(NULL));
    const int size = 100;
	//TODO generate de times and stuff
	long *arrayMS = generate_array(size);
	long *arrayQS = nullptr;
	copy_array<long>(arrayMS,arrayQS,size);
	//mostrar_array(arrayMS, size);
	
	qsort(arrayMS,size,sizeof(long),compare2);
	mostrar_array(arrayMS, size);
	std::chrono::steady_clock::time_point inicioMS = std::chrono::steady_clock::now();

	merge_sort(arrayMS,0,size-1);
	
	std::chrono::steady_clock::time_point finMS = std::chrono::steady_clock::now();
	auto timeMS = std::chrono::duration_cast<std::chrono::microseconds>( finMS - inicioMS).count()/1000000.0;

	mostrar_array(arrayMS, size);

	//mostrar_array(arrayMS, size);	
	//mostrar_array(arrayQS, size);
	
	qsort(arrayQS,size,sizeof(long),compare2);
	mostrar_array(arrayQS, size);
	std::chrono::steady_clock::time_point inicioQS = std::chrono::steady_clock::now();

	qsort(arrayQS,size,sizeof(long),compare);
	
	std::chrono::steady_clock::time_point finQS = std::chrono::steady_clock::now();
	auto timeQS = std::chrono::duration_cast<std::chrono::microseconds>( finQS - inicioQS).count()/1000000.0;
	mostrar_array(arrayQS, size);
	
	std::cout<<"MS time: "<< timeMS<<" QS time: "<<timeQS<<"\n";
	//mostrar_array(arrayQS, size);
	delete []arrayMS;
	delete []arrayQS;
}

void intercala(long*& array, const int indiceP, const int indiceQ, const int indiceR){
	// tamano r - p + 1
	const int sizeB = indiceR - indiceP + 1;
	long arrayAuxiliarB[sizeB];
	int i,j;
	int indiceArrayB = 0;

	for (i = indiceP; i <= indiceQ; ++i){
		arrayAuxiliarB[ indiceArrayB++ ] = array[i];
	}
	//segundo segmento cambia a forma descendente
	indiceArrayB = sizeB - 1;
	for(j = indiceQ + 1; j <= indiceR; ++j){
		arrayAuxiliarB[ indiceArrayB-- ] = array[j];
	}
	i = 0;
	j = sizeB - 1;
	for(int k = indiceP; k <= indiceR; ++k){
		if(	arrayAuxiliarB[i] <= arrayAuxiliarB[j]){
			array[k] = arrayAuxiliarB[i++];
		}
		else{
			array[k] = arrayAuxiliarB[j--];
		}
	}
}
void merge_sort(long*& array, const int indiceP, const int indiceR){
	if(indiceP < indiceR){
		int indiceQ = (indiceP + indiceR)/2;
		merge_sort(array,indiceP,indiceQ);
		merge_sort(array,indiceQ+1,indiceR);
		intercala(array, indiceP, indiceQ, indiceR);
	}
}

long* generate_array(const int size){
	long *array = new long[size]; 
	int i;
	for(i=0;i<size; ++i){
		array[i]= rand() % INF + 1;
	}
	return array;
}

void mostrar_array(long* array, const int size){
	for(int i=0;i<size; ++i)
		std::cout<<array[i]<<' ';
	std::cout<<std::endl;
}
template <typename T>
void mostrar_vector(std::vector<T>& myv){
	for(auto each: myv){
		std::cout << each<< ' ';
	}
	std::cout<<std::endl;
}
template <typename T>
T* copy_array(T*& arrayA, T*& arrayB,int size){
	arrayB = nullptr;
	T* temp = new T[size];
	for(int i=0; i < size; ++i)
		temp[i] = arrayA[i];
	arrayB = temp;
	return arrayB;
}
