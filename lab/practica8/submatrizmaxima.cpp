#include <iostream>

class MatrizInt{
	public:
		MatrizInt(int n){
			sizeMatriz = n;
			matriz = new int*[sizeMatriz];
			for(int i=0; i<sizeMatriz; ++i)
				matriz[i] = new int[sizeMatriz];

		}
		~MatrizInt(){
			for(int i=0; i<sizeMatriz; ++i){
				delete[] matriz[i];
			}
			delete[] matriz;
		}
		
		void add(int i, int j, int value){
			matriz[i][j] = value;
		}

		void llenar(){
			for(int i=0; i<sizeMatriz; ++i){
				for(int j =0; j<sizeMatriz; ++j){
					int value;
					std::cin >> value;
					add(i,j,value);
				}
			}

		}

		int size(){
			return sizeMatriz;
		}

		void print(){
			for(int i=0; i<sizeMatriz; ++i){
				for(int j=0; j<sizeMatriz; ++j){
					std::cout<< matriz[i][j]<<" ";
				}
				std::cout<<std::endl;
			}
		}

		int operator()(int i, int j){
			return matriz[i][j];
		}
	private:
		int sizeMatriz;
		int** matriz;
};

MatrizInt* crearMatrizAcumulacion(MatrizInt& matriz){

	int valueTopMA, valueLeftMA, valueTopLeftMA;
	int sizeMatriz = matriz.size();
	MatrizInt* matrizAcumulacion = new MatrizInt{sizeMatriz};

	for(int i=0; i<sizeMatriz; ++i){
		for(int j=0; j<sizeMatriz; ++j){
			if(i==0){
				valueTopMA = 0;
				valueTopLeftMA = 0;
			}
			else if(i>0){
				valueTopMA = (*matrizAcumulacion)(i-1,j);
			}
			if(j==0){
				valueLeftMA = 0;
				valueTopLeftMA = 0;
			}
			else if(j>0){
				valueLeftMA = (*matrizAcumulacion)(i,j-1);
			}
			if(i>0 && j>0){
				valueTopLeftMA = (*matrizAcumulacion)(i-1,j-1);
			}
			int value = matriz(i,j) + valueTopMA + valueLeftMA - valueTopLeftMA;
			
			matrizAcumulacion->add(i,j,value);
		}
	}

	return matrizAcumulacion;
}

int sumaSubMatriz(MatrizInt* matrizAcumulacion,int filaInicial, int columnaInicial, int filaFinal, int columnaFinal){
	int suma;
	int z, p, q, r;
	if(filaInicial == 0){
		p=0;
		r=0;
	}	
	else if(filaInicial >0){
		p = (*matrizAcumulacion)(filaInicial - 1, columnaFinal);
	}
	if(columnaInicial ==0){
		q=0;
		r=0;
	}
	else if(columnaInicial >0){
		q = (*matrizAcumulacion)(filaFinal, columnaInicial - 1);
	}
	if(columnaInicial > 0 && filaInicial > 0){
		r = (*matrizAcumulacion)(filaInicial - 1, columnaInicial - 1);
	}
	z = (*matrizAcumulacion)(filaFinal, columnaFinal);
	suma = z - p - q + r;	
	return suma;
}

void encontrarSubMatrizMaxima(MatrizInt* matrizAcumulacion, MatrizInt& matriz){
	int indiceFI, indiceCI, indiceFS, indiceCS;
	int sumaMax = (*matrizAcumulacion)(0,0);
	int size = matrizAcumulacion->size();
	for(int filaInferior = 0; filaInferior < size; ++filaInferior){
		for(int columnaInferior = 0; columnaInferior < size; ++columnaInferior){
			for(int filaSuperior = filaInferior; filaSuperior < size; ++filaSuperior){
				for(int columnaSuperior = columnaInferior; columnaSuperior < size; ++columnaSuperior){
					int sumaNueva;
					sumaNueva = sumaSubMatriz(matrizAcumulacion,filaInferior,columnaInferior,filaSuperior,columnaSuperior);
					if(sumaNueva > sumaMax){
						sumaMax = sumaNueva;
						indiceFI = filaInferior;
						indiceCI = columnaInferior;
						indiceFS = filaSuperior;
						indiceCS = columnaSuperior;
					}
				}
			}
		}
	}

	//mostrando resultado final
	for (int i = indiceFI; i <= indiceFS; ++i){
		for(int j = indiceCI; j<= indiceCS; ++j){
			std::cout<< matriz(i,j) <<" ";
		}
		std::cout<<std::endl;
	}
	std::cout << "Sumando "<<sumaMax<<std::endl;
}


int main(){
	int sizeMatriz;
	std::cin >> sizeMatriz;

	MatrizInt matrizEntrada{sizeMatriz};
	matrizEntrada.llenar();

	//creando matriz de acumulacion
	MatrizInt* matrizAcumulacion = crearMatrizAcumulacion(matrizEntrada);
	
	encontrarSubMatrizMaxima(matrizAcumulacion, matrizEntrada);
	delete matrizAcumulacion;
}
