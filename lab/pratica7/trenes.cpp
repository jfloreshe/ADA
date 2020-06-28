#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;
int find_media_en_permutacion(int arr[], int size){
	int i;
	int media = (size+1)/2;
	for(i=0;i<size;i++){
		if(arr[i]==media)
			break;	
	}
	return i;
}
int particiona(int arr[], int low, int high){
	int mediaIndice = find_media_en_permutacion(arr,high-low+1);
	int pivot = arr[mediaIndice]; 
	int i = (low-1);
	for(int j=low; j<= mediaIndice - 1 ; j++){
		if(arr[j] <= pivot){
			i++;
			swap(arr[i],arr[j]);
		}
	}
	swap(arr[i+1],arr[high]);
	return(i+1);
}
void printArray(int arr[], int size){
	int i;
	for(i =0; i<size;i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}
int main(){
	int A[]={4,3,2,1};
	printArray(A,4);
	particiona(A,0,3);
	printArray(A,4);	
}
