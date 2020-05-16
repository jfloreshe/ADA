/*/////////////////////////////////////////////////////////////////////////
Autor: Jefferson Miguel Flores Herrera								
Repositorio: https://github.com/jfloreshe/ADA/blob/master/tarea2.cpp
https://github.com/jfloreshe/ADA/blob/master/	
branch: master  													
Curso: Analisis y Diseno de Algoritmos Laboratorio A																
TAREA 3a: Analisis de insertion y merge sort. para que n elementos insertion sort es mejor que merge sort. Se agrega el metodo generar_txt LINEA 195 para resolver este problema. Se implemento el merge sort clasico.

Tarea 3b:Se implemento generar_txt_merge_intercala LINEA 237 para resolver este problema. Se implemento intercalacion y merge LINEA 118 y 144 en la LINEA 247 dentro de generar_txt_merge_intercala se puede ver que se hizo pa lprueba para ordenados y desordenados asi como la creaciones de variables globales asignaciones_merge e intercala_merge para tener en cuenta este aspecto aunque no tuve buenos resultados.
//////////////////////////////////////////////////////////////////////// */
#include <iostream>
#include <climits>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <utility>
#include <vector>

#define INF 50000
int asignaciones_merge = 0;
int asignaciones_intercala = 0;

long* generate_array(const int size);
long* insertion_sort(long*& array, const int size, bool(*compare)(void));
long* bubble_sort(long*& array, const int size, bool(*compare)(void));

void merge_sort_dinamico(long*& , const int indiceP, const int indiceR, void(*ordenacion)(long*& , const int , const int , const int ));

void merge_sort(long*& array, const int indiceP,const int indiceR);
void intercala(long*& array, const int indiceP,const int indiceQ, const int indiceR);
void merge(long*& array, const int indiceL,const int indiceM, const int indiceR);

void mostrar_array(long* array, const int size);

template <typename T>
T* copy_array(T*& arrayA, T*& arrayB, int size);

bool generar_txt(std::ofstream& fTabla);
bool generar_txt_merge_intercala(std::ofstream& fTabla);
bool mayor();
bool menor();

int main(){

	srand (time(NULL));	
	
	int size;

	std::ofstream fileTabla{"fileTabla2.txt"};

	generar_txt_merge_intercala(fileTabla);
	
	fileTabla.close();

}

long* generate_array(const int size){
	long *array = new long[size]; 
	int i;
	for(i=0;i<size; ++i){
		array[i]= rand() % INF + 1;
	}
	return array;
}

long* insertion_sort( long*& array, const int size, bool (*compare)(void)){
	int i, j;//no i,j,temp, as en i
	long temp;
	if(compare()){
		for(i=1;i< size; ++i){//as,co
			temp = array[i];//as
			j = i-1;//as
			while(j>=0 && array[j] > temp){
				array[j+1] = array[j];//as
				--j;//as j=j-1
			}
			array[j+1] = temp;//as
		}
	}	
	else{
		for(i=1;i< size; ++i){//as,co
			temp = array[i];//as
			j = i-1;//as
			while(j>=0 && array[j] < temp){
				array[j+1] = array[j];//as
				--j;//as j=j-1
			}
			array[j+1] = temp;//as
		}	
	}
	return array;
}

//IndiceP trabaja como el indice de la izquierda
//IndiceR trabaja como el indice de la Derecha
//IndiceQ trabaja como el indice intermedio que separa dos bloques de arrays de la misma cantidad de elementos +-1

void merge_sort(long*& array, const int indiceP, const int indiceR){
	if(indiceP < indiceR){
		int indiceQ = (indiceP + indiceR)/2;
		merge_sort(array,indiceP,indiceQ);
		merge_sort(array,indiceQ+1,indiceR);
		//intercala(array, indiceP, indiceQ, indiceR);
		merge(array, indiceP, indiceQ, indiceR);
	}

}
void merge_sort_dinamico(long*& array, const int indiceP, const int indiceR, void(*ordenacion)(long*& , const int, const int, const int)){
	if(indiceP < indiceR){
		int indiceQ = (indiceP + indiceR)/2;
		merge_sort(array,indiceP,indiceQ);
		merge_sort(array,indiceQ+1,indiceR);
		ordenacion(array, indiceP, indiceQ, indiceR);
	}
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
void merge(long*& array, const int indiceL, const int indiceM, const int indiceR){
	int i, j, k;
	const int tamanhoLeftArray = indiceM - indiceL + 1;
	const int tamanhoRightArray = indiceR - indiceM;
	
	long LeftArray[tamanhoLeftArray];
	long RightArray[tamanhoRightArray];
	
	for(i = 0; i < tamanhoLeftArray; i++){
		LeftArray[i] = array[indiceL + i];
	}
	for(j = 0; j < tamanhoRightArray; j++){
		RightArray[j] = array[indiceM + 1 + j];
	}

	i = 0;
	j = 0;
	k = indiceL;
	while( i < tamanhoLeftArray && j < tamanhoRightArray){
		if(LeftArray[i] <= RightArray[j]){
			array[k] = LeftArray[i++];
		}
		else{
			array[k] = RightArray[j++];
		}
		k++;
	}
	
	while (i < tamanhoLeftArray){
		array[k] = LeftArray[i++];
		k++;
	}

	while ( j < tamanhoRightArray){
		array[k] = RightArray[j++];
		k++;
	}
}
void mostrar_array(long* array, const int size){
	for(int i=0;i<size; ++i)
		std::cout<<array[i]<<' ';
	std::cout<<std::endl;
}

bool mayor(){
	return true;
}
bool menor(){
	return false;
}

bool generar_txt(std::ofstream & fTabla){
	long* arrayInsertion = nullptr;
	long* arrayMergeSort = nullptr;
	fTabla << "Tamanho\t"<<"Merge\t"<<"Insertion\n";
	for(int size = 1; size <1000; size++){
		arrayInsertion = generate_array(size);
		if(!copy_array<long>(arrayInsertion, arrayMergeSort, size)){
			std::cout<<"Fallo al crear el segundo array ... "<<size <<" elementos ... finalizando\n";
			delete[] arrayInsertion;
			delete[] arrayMergeSort;			
			arrayInsertion = nullptr;
			arrayMergeSort = nullptr;
			return false;
		}

		std::chrono::steady_clock::time_point inicioMS = std::chrono::steady_clock::now();
		
		merge_sort(arrayMergeSort, 0, size - 1);

		std::chrono::steady_clock::time_point finMS = std::chrono::steady_clock::now();
		auto timeMS = std::chrono::duration_cast<std::chrono::microseconds>( finMS - inicioMS).count()/1000000.0;

		fTabla << size << '\t' << timeMS << '\t';
		
		std::chrono::steady_clock::time_point inicioIS = std::chrono::steady_clock::now();
		
		insertion_sort(arrayInsertion, size, mayor);

		std::chrono::steady_clock::time_point finIS = std::chrono::steady_clock::now();
		auto timeIS = std::chrono::duration_cast<std::chrono::microseconds>( finIS - inicioIS).count()/1000000.0;

		fTabla << timeIS << '\n';
			
		
		delete[] arrayInsertion;
		delete[] arrayMergeSort;
		arrayInsertion = nullptr;
		arrayMergeSort = nullptr;
	}
	return true;
}

bool generar_txt_merge_intercala(std::ofstream & fTabla){
	int mejor = 0, igual = 0;
	long* arrayIntercala = nullptr;
	long* arrayMerge = nullptr;
	fTabla << "Tamanho\t"<<"Intercala\t"<<"Merge\n";

	std::vector<std::pair<int,std::pair<int,int>>> casosIntercalaEsMejor;

	for(int size = 1; size <10000; size++){
		arrayIntercala = generate_array(size);
		//insertion_sort(arrayIntercala,size,menor);
		//merge_sort(arrayIntercala,0,size-1);
		if(!copy_array<long>(arrayIntercala, arrayMerge, size) ){
			std::cout<<"Fallo al crear el segundo array ... "<<size <<" elementos ... finalizando\n";
			delete[] arrayIntercala;
			delete[] arrayMerge;			
			arrayIntercala= nullptr;
			arrayMerge= nullptr;
			return false;
		}

		std::chrono::steady_clock::time_point inicioIntercala = std::chrono::steady_clock::now();
		
		merge_sort_dinamico(arrayIntercala, 0, size - 1,intercala);
		std::chrono::steady_clock::time_point finIntercala = std::chrono::steady_clock::now();
		auto timeIntercala = std::chrono::duration_cast<std::chrono::microseconds>( finIntercala - inicioIntercala).count()/1000000.0;

		fTabla << size << '\t' << timeIntercala<< '\t';
		
		std::chrono::steady_clock::time_point inicioMerge = std::chrono::steady_clock::now();
		
		merge_sort_dinamico(arrayMerge, 0, size - 1,merge);
		std::chrono::steady_clock::time_point finMerge = std::chrono::steady_clock::now();
		auto timeMerge = std::chrono::duration_cast<std::chrono::microseconds>( finMerge - inicioMerge).count()/1000000.0;

		fTabla << timeMerge << '\n';
		if(timeIntercala < timeMerge){
			std::cout<<"Time Intercala es mejor en tamanho: "<<size<<std::endl;		
			mejor++;
			casosIntercalaEsMejor.push_back( std::make_pair(size,std::make_pair(asignaciones_merge,asignaciones_intercala)) );
			
		}
		else if(timeIntercala == timeMerge){
	//		std::cout<<"Time intercala es igual en tamanho: "<<size<<std::endl;
			igual++;
		}
		
		delete[] arrayIntercala;
		delete[] arrayMerge;
		arrayIntercala = nullptr;
		arrayMerge= nullptr;
	}

	std::cout<<"total veces que es mejor: "<<mejor<<"\ntotal vces que es igual: "<<igual<<"\ntotal veces que es peor: "<<10000 - mejor - igual<<std::endl;
/*	for(auto par: casosIntercalaEsMejor){
		std::cout<<"Intercalar es mejor en size: "<<par.first<<std::endl;
	}*/
	return true;
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

