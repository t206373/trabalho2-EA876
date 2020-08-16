#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <imageprocessing.h>

#define MAX 3
#define N 5

//Struct que auxilia para o caso de thread, já que podemos passar um arg para a função thread, facilitando assim mexer com a matriz antiga e a nova
typedef struct rgb{
	float *cor;
	void *n_cor;
	int x, y;
} rgb;

//Struct que junta as 3 matrizes em um só argumento, uma abstração e facilitação de passagem de argumentos
typedef struct arg{
	rgb r, g, b;
} arg;

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

//Função que chama o blur e retorna o novo valor da matriz, recebendo o argumento
void *thread(void *args){
	rgb *arg_1 = (rgb*) args; 					//Cast
	blur(arg_1->cor, arg_1->n_cor, arg_1->x, arg_1->y);		//Chama a função de blur com o rgb criado em cima								
	return NULL; 					
}

int main (){
	pthread_t r, g, b;
	rgb r_arg, g_arg, b_arg;
	void *r_pointer, *g_pointer, *b_pointer;
	
	r_pointer=&r_arg;
	g_pointer=&g_arg;
	b_pointer=&b_arg;
	
	//Abre imagem 
	imagem img;
 	img = abrir_imagem("data/liljoker.jpg");
	
	//Set de alguns variaveis de auxilio
	int a;
	int x = img.width;
  	int y = img.height;
	
	//Seta as informações necessárias para os argumentos de cada matriz
	r_arg.cor = img.r;
	r_arg.x = x;
	r_arg.y = y;
	r_arg.n_cor = malloc(sizeof(float)*x*y);
	
	g_arg.cor = img.g;
	g_arg.x = x;
	g_arg.y = y;
	g_arg.n_cor = malloc(sizeof(float)*x*y);

	b_arg.cor = img.b;
	b_arg.x = x;
	b_arg.y = y;
	b_arg.n_cor = malloc(sizeof(float)*x*y);

	//Cria as 3 threads necessárias para as matrizes
	pthread_create(&r, NULL, thread, r_pointer);
	pthread_create(&g, NULL, thread, g_pointer);
	pthread_create(&b, NULL, thread, b_pointer);

	pthread_join(r, NULL);
	pthread_join(g, NULL);
	pthread_join(b, NULL);
	
	//Passa da nova matriz para a matriz da imagem
	
   	img.r = (float*)r_arg.n_cor;
   	img.g = (float*)g_arg.n_cor;
   	img.b = (float*)b_arg.n_cor;
    
	
	//Libera a imagem com blur
	salvar_imagem("data/liljoker-thread-out.jpg", &img);
  	liberar_imagem(&img);
	
	return 0;
}
