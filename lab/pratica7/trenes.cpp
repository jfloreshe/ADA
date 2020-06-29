/*Autor: Jefferson Flores Herrera
 *Repositorio: https://github.com/jfloreshe/ADA/blob/master/lab/pratica7/trenes.cpp
 *Ejercicio: Swapear vagones consecutivos usando quicksort
 */
#include <iostream>
using namespace std;
int totalSwaps = 0;
void swap(int* a, int* b){
	int t= *a;
	 *a = *b;
	*b = t;
	totalSwaps++;
}
int find_indice_punto_medio_en_permutacion(int* arr, int low, int high){
	int i;
	int size = high - low + 1;
	int media = (high+1) - (size/2);
	for(i=low;i<=high;i++){
		if(arr[i]==media)
			break;	
	}
	return i;
}
int particiona(int* arr, int low, int high){
	int puntoMedioIndice= find_indice_punto_medio_en_permutacion(arr, low, high);
	int pivot = arr[puntoMedioIndice]; 
	int i;
	int j;
	for(i = puntoMedioIndice-1; i >= low; i--){
		if(arr[i] > pivot){
			int k=i;
			while(k < puntoMedioIndice){
				swap(&arr[k],&arr[k+1]);
				k++;
			}
			puntoMedioIndice--;
		}
		
	}
	for(j = puntoMedioIndice+1; j<=high; j++){
		if(arr[j] < pivot){
			int k=j;
			while(k > puntoMedioIndice){
				swap(&arr[k],&arr[k-1]);
				k--;
			}
			puntoMedioIndice++;
		}
	}	
	return(puntoMedioIndice);
}
void print_array(int* arr, int size){
	int i;
	for(i =0; i<size;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}
void quick_sort(int* arr, int low, int high){
	if(low < high){
		int indiceParticion = particiona(arr, low, high);
		quick_sort(arr, low, indiceParticion-1);
		quick_sort(arr, indiceParticion+1,high);
	}
}
int main(){
	int N;
	cin >> N;
	for(int i=0;i<N;i++){
		int L;
		cin >> L;
		int arr[L];
		totalSwaps=0;
		for(int j=0; j<L;j++){
			cin >> arr[j];
		}
		quick_sort(arr,0,L-1);
		cout<<"La mejor cantidad de swaps de trenes es " <<totalSwaps<<" swaps.\n";
	}
}
