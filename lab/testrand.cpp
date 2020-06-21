#include <stdio.h>
#include <ctime>
#include <random>
#include <algorithm>
#include <list>
#include <fstream>
int main(){
	std::ofstream file{"ok.txt"};
	srand(time(NULL));
	std::list<int> lista;
	int num;
	int repetidos=0;
	while(repetidos < 100){
		num = rand();
		//scanf("%d",&num);
		std::list<int>::iterator p;
		p= find(lista.begin(),lista.end(),num);
		if(p != lista.end()){
			printf("found despues de %ld elementos", lista.size());		
			repetidos ++;
			file << "total elementos: "<< lista.size() << " total repetidos: "<< repetidos << "\n";
		}
		printf("%d, size= %ld\n",num,lista.size());
		lista.push_back(num);
	}
	file.close();
}
