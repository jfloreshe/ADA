/*
Practica 4 - ADA Laboratorio A
Codigo Lineal
Alumno: Jefferson Flores Herrera
git: https://github.com/jfloreshe/ADA/tree/master/lab
*/
#include <stdio.h>
int seg_max_lin(int* A,const int n,int& e,int& d){
	int sumamax = 0;
	e= 0;
	d= -1;
	int suma = 0;
	int i = 0;
	int f = 0;
	while(f<n){
		suma += A[f++];
		if(suma < 0){
			suma = 0;
			i = f;
		}
		else if (suma >= sumamax){
			sumamax = suma;
			e=i;
			d=f-1;
		}
	}
	return sumamax;
}
int main(){
	int R;
	scanf("%d",&R);
	for(int rr=1;rr<=R;rr++){
		int* rArrayCalles{nullptr};
		int C;
		scanf("%d",&C);
		int vArraySize = C-1;
		rArrayCalles = new int[vArraySize];
		for(int i=0; i<vArraySize;i++){
			scanf("%d",&rArrayCalles[i]);
		}
		int rCalleInicio,rCalleFinal;
		if(seg_max_lin(rArrayCalles,vArraySize,rCalleInicio,rCalleFinal)<=0){
			printf("La ruta %d no tiene calles interesantes\n",rr);
		}
		else{
			printf("La mejor parte de la ruta %d es entre las calles %d y %d\n",rr,rCalleInicio+1,rCalleFinal+2);
		}
		delete[] rArrayCalles;
	}	
}
