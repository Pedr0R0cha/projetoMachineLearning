#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  Aqui ficarão os protótipos das funções

int main(void) {

  int i, j;
  FILE *fp;
  float vetorLinhaTemporario[3] = {};
  char string[14];
  char valorEmString[5];
  char diretorio[500];

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

  } while (!feof(fp));
  

  fclose(fp);


  return 0;
}


//Funções