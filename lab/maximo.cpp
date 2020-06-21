/*
Practica 6 - ADA Laboratorio A
Alumno: Jefferson Flores Herrera
Repositorio:  https://github.com/jfloreshe/ADA/tree/master/lab/maximo.cpp
*/
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#define INF 20000
#define TOTALTEST 200
long* generate_array(const long);
long* generate_array_diferentes(const long);
long max(long*, long, long&);
void mostrar_array(long* , const long);
double promedioMaxLinea4(long*);


long Resultado[TOTALTEST];
int main(){
	std::ofstream xlstabla{"lab6.txt"};
	const int base = 2;
	int exptamano = 8;

	srand (time(NULL));
	
	for(exptamano; exptamano<=20; exptamano++){
		long size = 1;
		for(int i=1;i<=exptamano;i++){
			size *= base;
		}
		for(int totalTest=1;totalTest<=TOTALTEST;totalTest++){
			long*A = generate_array_diferentes(size);
			long totalLinea4 = 0;
			max(A,size,totalLinea4);
			Resultado[totalTest-1] = totalLinea4;
			delete[]A;
			A = nullptr;
		}
		xlstabla << size<<'\t';
		printf("%ld ",size);
		double promedio = promedioMaxLinea4(Resultado);
		xlstabla << promedio<<'\n';
		std::cout << promedio << std::endl;	
	}
	xlstabla.close();
}
long* generate_array(const long size){
	long *array = new long[size]; 
	long i;
	for(i=0;i<size; ++i){
		array[i]= rand();
	}
	return array;
}
long* generate_array_diferentes(const long size){
	long *array = new long[size]; 
	for(long i=0;i<size;++i){
		array[i]=i+1;
	}
	int currentTotalSwaps=0, randomFirstPos=0, randomSecondPos=0, swaps=0, temp=0;
	swaps = rand()%size +size;
	while(currentTotalSwaps<swaps){
		randomFirstPos=rand()%size;
		temp = array[randomFirstPos];
		randomSecondPos = rand()%size;
		array[randomFirstPos] = array[randomSecondPos];
		array[randomSecondPos] = temp;
		++currentTotalSwaps;
	}
	return array;
}
double promedioMaxLinea4(long* A){
	double promedio =0;
	for(int i=0; i<TOTALTEST; i++){
		promedio += A[i];
	}
	promedio /= (TOTALTEST*1.0f);
	return promedio;
}
void mostrar_array(long* array, const long size){
	for(int i=0;i<size; ++i)
		std::cout<<array[i]<<' ';
	std::cout<<std::endl;
}

long max(long*A, long size, long& totalLinea4){
	long max = A[0];
	for(long i=1;i<size;i++){
		if(A[i]>max){
			max = A[i];
			totalLinea4++;
		}
	}
	return max;
}
