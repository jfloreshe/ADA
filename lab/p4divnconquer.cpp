/*
Practica 4 - ADA Laboratorio A
Codigo Divide y venceras
Alumno: Jefferson Flores Herrera
git: https://github.com/jfloreshe/ADA/tree/master/lab
*/
#include<stdio.h>
int max(int a, int b){return a>=b?a:b;}
int max(int a, int b, int c){
	return max(max(a,b),c);
}
int seg_max_dv(int* A,int p, int r,int& izqIndice,int& derIndice){
	if(p==r)
		return max(0,A[p]);
	int q = (p+r)/2;
	int maxizq = seg_max_dv(A,p,q,izqIndice,derIndice);
	int maxder = seg_max_dv(A,q+1,r,izqIndice,derIndice);

	int suma = A[q];
	int max2izq = suma;
	izqIndice = q;
	for(int i= q-1; i>=p; i--){
		suma += A[i];
		if(suma>=max2izq)
			izqIndice = i;
		max2izq = max(max2izq,suma);	
	}
	suma = A[q+1];
	int max2der = suma;
	derIndice = q+1;
	for(int i = q+2; i<=r;i++){
		suma += A[i];
		if(suma>=max2der)
			derIndice = i;
		max2der = max(max2der,suma);
	}
	int maxcruz =  max2izq + max2der;
	if(maxizq == 0) izqIndice = derIndice;
	return max(maxizq,maxcruz,maxder);
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
		if(seg_max_dv(rArrayCalles,0,vArraySize-1,rCalleInicio,rCalleFinal)<=0){
			printf("La ruta %d no tiene calles interesantes\n",rr);
		}
		else{
			printf("La mejor parte de la ruta %d es entre las calles %d y %d\n",rr,rCalleInicio+1,rCalleFinal+2);
		}
		delete[] rArrayCalles;
	}	
}
