#include <imageprocessing.h>
#include <stdlib.h>
#include <stdio.h>

//função de blur
void blur (float *matriz, float *nova, int comeco_i, int fim_i, int comeco_j, int fim_j, int indice, int x){

  int i, j, tmp=0, count = 0;
  
  for(i=comeco_i; i < fim_i; i++){
    for(j=comeco_j; j < fim_j; j++){
      tmp += matriz[j*x+i];
      count++;
    }
    nova[indice] = tmp / count;
  }
}

int main(){
	imagem img, nova;
	img = abrir_imagem("data/joker.jpg");
	nova = abrir_imagem("data/joker.jpg");
	int fim_i, fim_j, comeco_i, comeco_j;
	int i, j, x, y, N;
	  
	N=5;
	x=img.width;
	y=img.height;

	//Verifica os ranges do quadrado para aplicar o blur, e seta constantes
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
	    //Aplica o blur nas matrizes novas 
	    blur(img.r, nova.r, comeco_i, fim_i, comeco_j, fim_j, j*x+i, x);
	    blur(img.g, nova.g, comeco_i, fim_i, comeco_j, fim_j, j*x+i, x);
	    blur(img.b, nova.b, comeco_i, fim_i, comeco_j, fim_j, j*x+i, x);
	  }
	}
	//Libera a imagem nova
	salvar_imagem("data/joker-out.jpg", &nova);
	liberar_imagem(&img);
	liberar_imagem(&nova);
	return 0;
}