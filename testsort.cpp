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
#include <fstream>
#define INF 1000000

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
////////Graph generator util////////
bool generar_txt_tiempos(std::ofstream&);
////////////MAIN//////////////
int main(){
	srand (time(NULL));
	std::ofstream xls{"QSMS.txt"};
	generar_txt_tiempos(xls);
	xls.close();
}
bool generar_txt_tiempos(std::ofstream& xls){
	int mejor = 0, igual = 0,i = 1;
	int sizeEstatico = 1000;
	long* arrayQS = nullptr;
	long* arrayMS = nullptr;
	long* arrayTemp = nullptr;
	xls << "Tamanho\t"<<"MS\t"<<"QS\n";
		
	for(int size = sizeEstatico; size <=500000; i++,size=sizeEstatico*i){
//	for(int size = 1; size <=1000; size++){
		arrayQS = generate_array(size);
		//ordenar array en este espacio para otra comparacion
		if(!copy_array<long>(arrayQS, arrayMS, size) || !copy_array<long>(arrayQS,arrayTemp, size) ){
			std::cout<<"Fallo al crear el segundo array ... "<<size <<" elementos ... finalizando\n";
			delete[] arrayQS;
			delete[] arrayMS;
			delete[] arrayTemp;
			arrayQS= nullptr;
			arrayMS= nullptr;
			arrayTemp= nullptr;
			return false;
		}


		std::chrono::steady_clock::time_point inicioMS = std::chrono::steady_clock::now();

		merge_sort(arrayMS,0,size-1);
		
		std::chrono::steady_clock::time_point finMS = std::chrono::steady_clock::now();
		auto timeMS = std::chrono::duration_cast<std::chrono::microseconds>( finMS - inicioMS).count()/1000000.0;
		
		xls << size << '\t' << timeMS<< '\t';

		std::chrono::steady_clock::time_point inicioQS = std::chrono::steady_clock::now();

		qsort(arrayQS,size,sizeof(long),compare);
			
		std::chrono::steady_clock::time_point finQS = std::chrono::steady_clock::now();
		auto timeQS = std::chrono::duration_cast<std::chrono::microseconds>( finQS - inicioQS).count()/1000000.0;

		xls << timeQS << '\n';
		if(timeQS > timeMS){
			std::cout<<"Time MS es mejor en tamanho: "<<size<<std::endl;		
			mostrar_array(arrayTemp,size);
			mejor++;
		}
		else if(timeQS == timeMS){
	//		std::cout<<"Time MS es igual en tamanho: "<<size<<std::endl;
			igual++;
		}
		
		delete[] arrayQS;
		delete[] arrayMS;
		delete[] arrayTemp;
		arrayQS = nullptr;
		arrayMS= nullptr;
		arrayTemp= nullptr;
	}

	std::cout<<"total veces que MS es mejor: "<<mejor<<"\ntotal veces que MS es igual: "<<igual<<"\ntotal veces que MS es peor: "<<i - mejor - igual<<std::endl;
	return true;

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
