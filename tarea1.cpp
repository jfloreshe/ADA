#include <iostream>
#include <climits>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>

#define INF LONG_MAX
#define ul unsigned long
#define ull unsigned long long

/*PARA COMPILAR
	g++ -pthreads -std=c++11 tarea1.cpp -o tarea1
*/
/*
	no= creacion nuevo objeto;
	as= asignacion;
	co= comparacion;
	arr= alloc on new array;
*/
void generateArray(long*& array,const ul size);
void insertionSort(long*& array, const ul size);
void bubbleSort(long*& array, const ul size);
ull cantidad_objetos=0, cantidad_comparaciones=0, cantidad_asignaciones=0, cantidad_memoria=0;

int main(){
	srand (time(NULL));	
	long* array = nullptr;//as,no
	long* array2 = nullptr;//as,no
	cantidad_asignaciones+=2;
	cantidad_objetos+=2;
	ul size;//no
	cantidad_objetos++;
	std::cout<<"Ingrese tamano a generar\n";
	std::cin>>size;//as no estoy seguro de esto
	cantidad_asignaciones++;
	
	std::thread arrayinsertion (generateArray,std::ref(array),size);//no
	std::thread arraybubble (generateArray,std::ref(array2),size);//no
	cantidad_objetos+=2;

	std::cout<<" arrays generados\n";
	arrayinsertion.join();//thread
	arraybubble.join();//thread

	std::thread thread_insertion (insertionSort,std::ref(array),size);//no
	std::thread thread_bubble (bubbleSort,std::ref(array2),size);//no
	cantidad_objetos += 2;

	thread_insertion.join();//thread
	thread_bubble.join();//thread
	delete[] array;
	delete[] array2;
	cantidad_objetos*=200;
	cantidad_asignaciones*=8;
	cantidad_comparaciones*=2;
	std::cout<<"analisis cantidad objetos: "<< cantidad_objetos<<std::endl
			 <<"analisis cantidad asignaciones: "<< cantidad_asignaciones<<std::endl
			 <<"analisis cantidad de comparaciones: "<< cantidad_comparaciones<<std::endl
			 <<"analisis cantidad de asignacion de memoria: "<<cantidad_memoria<<std::endl;
}

void generateArray(long*& array, const ul size){
	//delete[] array //--si necesitamos hacer constantes pruebas.
	cantidad_objetos++;//no size
	cantidad_asignaciones++;//as en argumento size ya que es un nuevo objeto copia
	array = new long[size]; //arr
	cantidad_memoria += 50 + size*10;
	ul i;//no
	cantidad_objetos++;
	cantidad_asignaciones++;//as para iniciar el for i=0
	cantidad_comparaciones++;//co para entrar al for
	for(i=0;i<size; ++i){//as,co
		array[i]= rand() % INF + 1;//as
		cantidad_asignaciones++;
		//	std::cout<< array[i]<<", ";//imprime array desordenado
		cantidad_asignaciones++;//as para++i i=i+1;
		cantidad_comparaciones++;//co para seguir en el for
	}
}
void insertionSort( long*& array, const ul size){
	std::chrono::steady_clock::time_point inicio_ordenamiento_insertion = std::chrono::steady_clock::now();//c++11 time
	cantidad_objetos++;//no size
	cantidad_asignaciones++;// as size
	ul i, j, temp;//no i,j,temp, as en i
	cantidad_objetos += 3;	
	cantidad_asignaciones++;//as para iniciar el for i=0
	cantidad_comparaciones++;//co para entrar al for
	for(i=0;i< size; ++i){//as,co
		j =i;//as
		cantidad_asignaciones++;
		cantidad_comparaciones+=2;//2 co para entrar al while
		while(j>0 && array[j] < array[j-1]){
			temp = array[j];//as
			cantidad_asignaciones++;
			array[j]= array[j-1];//as
			cantidad_asignaciones++;
			array[j-1] = temp;//as
			cantidad_asignaciones++;
			j--;//as j=j-1
			cantidad_asignaciones++;
			cantidad_comparaciones += 2;//2 co para ejecutar de neuvo el while
		}
		cantidad_asignaciones++;//as para ++i i=i+1
		cantidad_comparaciones++;//co para continuar en el for
	}
	std::chrono::steady_clock::time_point fin_ordenamiento_insertion = std::chrono::steady_clock::now();//c++11 time
	std::cout<<"Tiempo de insert sort: "<< std::chrono::duration_cast<std::chrono::microseconds>(fin_ordenamiento_insertion - inicio_ordenamiento_insertion).count()/1000000.0<<" segundos" <<std::endl;
}
void bubbleSort(long*& array, const ul size){
	std::chrono::steady_clock::time_point inicio_ordenamiento_bubble = std::chrono::steady_clock::now();//c++11 time
	cantidad_objetos++;//no size
	cantidad_asignaciones++;// as size
	ul i, j;//no
	cantidad_objetos += 2;
	cantidad_asignaciones++;//as para iniciar el for i=0
	cantidad_comparaciones++;//co para entrar al for
	for(i=0;i< size-1;++i){//as,co
		cantidad_asignaciones++;//as para iniciar el for j=0
		cantidad_comparaciones++;//co para entrar al for
		for(j=0; j< size-i-1; ++j){
			if(array[j] > array[j+1]){
				int temp = array[j];//no,as
				cantidad_objetos++;
				cantidad_asignaciones++;
				array[j] = array[j+1];//as
				array[j+1] = array[j];//as
				cantidad_asignaciones+=2;
			}	
			cantidad_asignaciones;//as para ++j;
			cantidad_comparaciones;//co para continuar en el for
		}
		cantidad_asignaciones++;//as para ++i
		cantidad_comparaciones++;//co para continuar en el for
		
	}
	std::chrono::steady_clock::time_point fin_ordenamiento_bubble = std::chrono::steady_clock::now();
	std::cout<<"Tiempo de bubble sort: "<< std::chrono::duration_cast<std::chrono::microseconds>(fin_ordenamiento_bubble - inicio_ordenamiento_bubble).count()/1000000.0<<" segundos" <<std::endl;
}
