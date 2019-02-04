#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Aqui ficarão os protótipos das funções
int retornaAleatorio();

int main(void) {

  int i, j;
  int pesos[2] = {retornaAleatorio(), retornaAleatorio()};
  FILE *fp;
  float vetorLinhaTemporario[3] = {};
  char string[14];
  char valorEmString[5];
  char diretorio[500];
  float valorAprendido = 0;
  float erro = 0;
  float alfa = 0.001;

  printf("Digite o diretório ");
  scanf("%s", diretorio);

  fp = fopen(diretorio, "r");

  if(fp == NULL) {
    printf("Não é possivel ler o arquivo, redigite o nome do arquivo");
  }

  do {

    fgets(string, 14, fp);
    fscanf(fp, "%f;%f;%f", &vetorLinhaTemporario[0], &vetorLinhaTemporario[1], &vetorLinhaTemporario[2]);
    printf("%.2f %.2f %.2f\n", vetorLinhaTemporario[0], vetorLinhaTemporario[1], vetorLinhaTemporario[2]);

    int cont;
    for ( cont = 0; cont < 2; cont++ ) {
      valorAprendido += pesos[cont] * vetorLinhaTemporario[cont];
    }
    valorAprendido = valorAprendido > 0 ? 1 : 0;

    erro = vetorLinhaTemporario[2] - valorAprendido;
    if ( erro == 0 ) {
      printf("Acertou ó");
    }
    
    for ( cont = 0; cont < 2; cont++ ) {
      pesos[cont] = pesos[cont] + ( alfa * erro * vetorLinhaTemporario[cont] );
    }

  } while (!feof(fp));
  

  fclose(fp);


  return 0;
}


//Funções

int retornaAleatorio() {

  srand(time(NULL));

  return (rand() % 9);

}