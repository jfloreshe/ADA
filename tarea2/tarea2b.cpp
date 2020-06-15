/*//////////////////////////////////////////////////////////
Autor: Jefferson Miguel Flores Herrera					////
Repositorio: https://github.com/jfloreshe/ADA.git		////
branch: master  										////
Curso: Analisis y Diseno de Algoritmos Laboratorio A	////
														////
TAREA 2: Analisis de insertion y bubble sort, en tiempo ////
real costo retornado por el analisis con elementos 		////
ordenados crecientemente, ordenados decrecientemente 	////
y desordenados 											////
///////////////////////////////////////////////////////// */
#include <iostream>
#include <climits>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>

#define INF 50000
typedef unsigned long long ull;

long* generate_array(const int size);
long* insertion_sort(long*& array, const int size, bool(*compare)(void));
long* bubble_sort(long*& array, const int size, bool(*compare)(void));
void mostrar_array(long* array, const int size);
bool mayor();
bool menor();

int main(){

	srand (time(NULL));	
	
	int size;
	
	std::cout<<"Ingrese tamano a generar\n";
	std::cin>>size;

	long* arrayDesordenadoInsertion = generate_array(size);
	long* arrayDesordenadoBubble = generate_array(size);
	long* arrayOrdenadoDescendenteInsertion = generate_array(size);
	long* arrayOrdenadoDescendenteBubble = generate_array(size);
	
	if(arrayDesordenadoInsertion && arrayDesordenadoBubble && arrayOrdenadoDescendenteInsertion && arrayOrdenadoDescendenteBubble){		
		//ordenando descendentemente
		insertion_sort(arrayOrdenadoDescendenteInsertion,size,menor);
		insertion_sort(arrayOrdenadoDescendenteBubble,size,menor);
		
		std::cout<<"\nARRAYS DESORDENADOS\n";		
		long* arrayOrdenadoAscendenteInsertion = insertion_sort(arrayDesordenadoInsertion, size, mayor);
		long* arrayOrdenadoAscendenteBubble = bubble_sort(arrayDesordenadoBubble, size, mayor);
		
		std::cout<<"\nARRAYS ORDENADOS ASCENDENTEMENTE\n";
		insertion_sort(arrayOrdenadoAscendenteInsertion, size, mayor);
		bubble_sort(arrayOrdenadoAscendenteBubble, size, mayor);
			
		std::cout<<"\nARRAYS ORDENADOS DESCENDENTEMENTE\n";
		insertion_sort(arrayOrdenadoDescendenteInsertion, size, mayor);
		bubble_sort(arrayOrdenadoDescendenteBubble, size, mayor);
		
	}
	else
		std::cout<<"error en la creacion de arrays";
	
	delete[] arrayDesordenadoInsertion;
	delete[] arrayDesordenadoBubble;
	delete[] arrayOrdenadoDescendenteInsertion;
	delete[] arrayOrdenadoDescendenteBubble;
}

long* generate_array(const int size){
	long *array = new long[size]; 
	int i;
	for(i=0;i<size; ++i){
		array[i]= rand() % INF + 1;
	}
	std::cout<<"Array Generado\n";
	//mostrar_array(array,size);
	return array;
}

long* insertion_sort( long*& array, const int size, bool (*compare)(void)){
	ull cantidad_comparaciones_insert=0;
	ull cantidad_asignaciones_insert=0;
	ull cantidad_objetos_insert=0;
	std::chrono::steady_clock::time_point inicio_ordenamiento_insertion = std::chrono::steady_clock::now();//c++11 time
	int i, j;//no i,j,temp, as en i
	long temp;

	cantidad_objetos_insert += 3;
	++cantidad_comparaciones_insert;
	if(compare()){
		
		++cantidad_asignaciones_insert;
		++cantidad_comparaciones_insert;
		
		for(i=1;i< size; ++i){//as,co
		
			temp = array[i];//as
			j = i-1;//as

			cantidad_asignaciones_insert +=2;
			cantidad_comparaciones_insert +=2;
			while(j>=0 && array[j] > temp){
				array[j+1] = array[j];//as
				--j;//as j=j-1
				cantidad_asignaciones_insert +=2;
				cantidad_comparaciones_insert +=2;
			}
			array[j+1] = temp;//as
			++cantidad_asignaciones_insert;

			++cantidad_asignaciones_insert;
			++cantidad_comparaciones_insert;
		}
	}	
	else{
		++cantidad_asignaciones_insert;
		++cantidad_comparaciones_insert;
		for(i=1;i< size; ++i){//as,co
			temp = array[i];//as
			j = i-1;//as
			cantidad_asignaciones_insert += 2;
			cantidad_comparaciones_insert += 2;
			while(j>=0 && array[j] < temp){
				array[j+1] = array[j];//as
				--j;//as j=j-1
				cantidad_asignaciones_insert +=2;
				cantidad_comparaciones_insert +=2;
			}
			array[j+1] = temp;//as
			++cantidad_asignaciones_insert;
			
			++cantidad_asignaciones_insert;
			++cantidad_comparaciones_insert;
		}	
	}
	std::chrono::steady_clock::time_point fin_ordenamiento_insertion = std::chrono::steady_clock::now();//c++11 time

	cantidad_comparaciones_insert *=2 ;
	cantidad_asignaciones_insert *=8 ;
	cantidad_objetos_insert *=200 ;
	ull total = cantidad_comparaciones_insert + cantidad_asignaciones_insert + cantidad_objetos_insert;
	std::cout<<"INSERTION SORT\n";
	std::cout<<"Tiempo de insert sort: "<< std::chrono::duration_cast<std::chrono::microseconds>(fin_ordenamiento_insertion - inicio_ordenamiento_insertion).count()/1000000.0<<" segundos" <<std::endl<<"Comparaciones realizadas: "<< cantidad_comparaciones_insert<<std::endl<<"Asignaciones realizadas: "<<cantidad_asignaciones_insert<<std::endl<<"Objetos creados: "<<cantidad_objetos_insert<<std::endl<<"Tiempo Total: "<<total<<std::endl;
	return array;
}
long* bubble_sort(long*& array, const int size,bool(*compare)(void)){
	ull cantidad_asignaciones_bubble = 0;
	ull cantidad_objetos_bubble = 0;
	ull cantidad_comparaciones_bubble = 0;
	std::chrono::steady_clock::time_point inicio_ordenamiento_bubble = std::chrono::steady_clock::now();//c++11 time
	int i, j;//no
	cantidad_objetos_bubble += 2;
	++cantidad_comparaciones_bubble;

	if(compare()){
		++cantidad_asignaciones_bubble;
		++cantidad_comparaciones_bubble;
		for(i=0;i< size-1;++i){//as,co
			++cantidad_asignaciones_bubble;
			++cantidad_comparaciones_bubble;
			for(j=0; j< size-i-1; ++j){
				++cantidad_comparaciones_bubble;
				if(array[j] > array[j+1]){
					long temp = array[j];//no,as
					array[j] = array[j+1];//as
					array[j+1] = temp;//as
					cantidad_asignaciones_bubble += 3;
				}	
				++cantidad_asignaciones_bubble;
				++cantidad_comparaciones_bubble;				
			}		
			++cantidad_asignaciones_bubble;
			++cantidad_comparaciones_bubble;
		}
	}
	else{
		++cantidad_asignaciones_bubble;
		++cantidad_comparaciones_bubble;
		for(i=0;i< size-1;++i){//as,co
			++cantidad_asignaciones_bubble;
			++cantidad_comparaciones_bubble;
			for(j=0; j< size-i-1; ++j){
				++cantidad_comparaciones_bubble;
				if(array[j] < array[j+1]){
					long temp = array[j];//no,as
					array[j] = array[j+1];//as
					array[j+1] = temp;//as
					cantidad_asignaciones_bubble +=3;
				}	
				++cantidad_asignaciones_bubble;
				++cantidad_comparaciones_bubble;
			}		
			++cantidad_asignaciones_bubble;
			++cantidad_comparaciones_bubble;
		}	
	}
	std::chrono::steady_clock::time_point fin_ordenamiento_bubble = std::chrono::steady_clock::now();
	
	cantidad_comparaciones_bubble *=2 ;
	cantidad_asignaciones_bubble *=8 ;
	cantidad_objetos_bubble *=200 ;
	ull total = cantidad_comparaciones_bubble + cantidad_asignaciones_bubble + cantidad_objetos_bubble;
	
	std::cout<<"BUBBLE SORT\n";
	std::cout<<"Tiempo de bubble sort: "<< std::chrono::duration_cast<std::chrono::microseconds>(fin_ordenamiento_bubble - inicio_ordenamiento_bubble).count()/1000000.0<<" segundos" <<std::endl<<"Comparaciones realizadas: "<<cantidad_comparaciones_bubble<<std::endl<<"Asignaciones realizadas: "<< cantidad_asignaciones_bubble<<std::endl<<"Objetos creados: "<<cantidad_objetos_bubble<<std::endl<<"Tiempo total: "<<total<<std::endl;
	return array;
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
