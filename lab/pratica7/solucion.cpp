/*
Autor: Jefferson Flores Herrera
github: 
Ejercicio: Encontrar el punto medio de 8000 elementos
*/
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

#define MX 2000000000
int particiona(long arr[], int low, int high){
	long pivot = arr[high];
	int i = (low-1);
	for(int j=low; j<= high - 1 ; j++){
		if(arr[j] <= pivot){
			i++;
			swap(arr[i],arr[j]);
		}
	}
	swap(arr[i+1],arr[high]);
	return(i+1);
}
void swap(long* a, long* b){
	long t= *a;
	 *a = *b;
	*b = t;
}
void printArray(long arr[], int size){
	int i;
	for(i =0; i<size;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}
void maxValue(long A[],long low,long high,long& pos,long& max){
	max = A[low];
	pos = low;
	for(long i=low+1;i<=high;i++){
		if(A[i]>max){
			max = A[i];
			pos = i;
		}
	}
}
void minValue(long A[],long low,long high,long& pos,long& min){
	min = A[low];
	pos = low;
	for(long i=low+1;i<=high;i++){
		if(A[i]<min){
			min = A[i];
			pos = i;
		}
	}
}
int main(){
	int n=8000;
	long temp;
	for(int i=0; i<n ; i++){
		long array[n+1];
		long long sum = 0;
		cin >> temp;
		for(int j=0;j<n;j++){
			cin >> array[j];
			sum += array[j];
		}
		sum /= n;
		//sum es la media y se ingresa
		array[n]=sum;
		//usando particiona y encontrando la posicion del pivote
		int pos = particiona(array,0,n);
		long mediumValue;
		//casos de la posicion del pivote
		if(pos == n/2){
			long posMax=0;
			maxValue(array,0,pos-1,posMax,mediumValue);
		}
		else if(pos < n/2){
			//calcula la distancia y de acuerdo a la distancia elimina elementos para encontrar el k minimo
			int totalDeletes = n/2 - pos-1;	
			long posMin=0;
			while (totalDeletes >0){
				minValue(array,pos+1,n,posMin,mediumValue);
				array[posMin] = MX;
				totalDeletes--;
			}
			//despues de eliminar k elementos se calcula el punto medio
			minValue(array,pos+1,n,posMin,mediumValue);
		}
		else if(pos > n/2){
			//calcula la distancia y de acuerdo a la distancia elimina elementos para encontrar el k maximo 
			int totalDeletes = pos - n/2;	
			long posMax=0;

			while (totalDeletes >0){
				maxValue(array,0,pos-1,posMax,mediumValue);
				array[posMax] = 0;
				totalDeletes--;
			}
			//despues de eliminar k elementos se calcula el punto medio
			maxValue(array,0,pos-1,posMax,mediumValue);
		}
		printf("%ld\n",mediumValue);
//		cout<<mediumValue<<endl;
	}
	return 0;
}
