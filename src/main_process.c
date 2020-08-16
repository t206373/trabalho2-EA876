#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <imageprocessing.h>

#define N 5

//função de blur
void blur (float *matriz, float *nova, int x, int y){

  int fim_i, fim_j, comeco_i, comeco_j;
  int i, j, k, l, tmp=0, count = 0;
  
  for(i=0; i < x; i++){
    	for(j=0; j < y; j++){
		    if(i-N < 0)
		      	comeco_i=0;
		    else
		        comeco_i=i-N;
		    if(i+N > x)
		        fim_i=x;
		    else
		        fim_i=i+N;
		    if(j-N < 0)
		        comeco_j=0;
		    else
		        comeco_j=j-N;
		    if(j+N > y)
		        fim_j=y;
		    else
		        fim_j=j+N;
		    for(k=comeco_i; k < fim_i; k++){
    			for(l=comeco_j; l < fim_j; l++){
      				tmp += matriz[l*x+k];
      				count++;
      			}
      		}
      		nova[j*x+i] = tmp / count;
      		tmp = 0;
      		count = 0;
      	}
    }
}

int main() {
	pid_t p[3]={-1, -1, -1};

	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANON;
	float *shared_r, *shared_g, *shared_b;

	imagem img;
 	img = abrir_imagem("data/liljoker.jpg");
 	int a, x, y;

  	x=img.width;
  	y=img.height;
	
	//Cria as 3 matrizes na memória compartilhada
  	shared_r = (float*) mmap(NULL, sizeof(float)*x*y, protection, visibility, 0, 0);
	shared_g = (float*) mmap(NULL, sizeof(float)*x*y, protection, visibility, 0, 0);
	shared_b = (float*) mmap(NULL, sizeof(float)*x*y, protection, visibility, 0, 0);

	//Cria 3 processos filhos, porém sempre quando está no pai
	p[0] = fork();
	if(p[0] != 0)
		p[1] = fork();
	if(p[0] != 0 && p[1] != 0)
		p[2] = fork();
	
	//Se está no porcesso filho, aplica o blur nas matrizes compartilhadas
	if(p[0]==0){
		blur(img.r, shared_r, x, y);
	}
	if(p[1]==0){
    		blur(img.g, shared_g, x, y);
	}
    	if(p[2]==0){
    		blur(img.b, shared_b, x, y);
    	}

	//Se está no processo pai, espera todos os filhos acabarem
    	if(p[0] != 0 && p[1] != 0 && p[2] != 0){
    		waitpid(p[0], NULL, 0);
    		waitpid(p[1], NULL, 0);
  		waitpid(p[2], NULL, 0);
  		for (a=0; a < x*y; a++){ //Passa da nova matriz para a matriz da imagem
  			img.r[a]=shared_r[a];
  			img.g[a]=shared_g[a];
  			img.b[a]=shared_b[a];
  		}
		//Libera a imagem
		salvar_imagem("data/liljoker-process-out.jpg", &img);
  		liberar_imagem(&img);
	}
	return 0;
}
