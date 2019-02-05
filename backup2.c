#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Aqui ficarão os protótipos das funções
int retornaAleatorio();

int main(void) {

  int i, j;
  int contadorExterno = 0;
  int pesos[2] = {retornaAleatorio(), retornaAleatorio()};
  FILE *fpAprende;
  float vetorLinhaTemporario[3] = {};
  char string[14];
  char valorEmString[5];
  char diretorioAprendizado[500];
  float valorAprendido = 0;
  float erro = 0;
  float alfa = 0.001;

  printf("Digite o diretório ");
  scanf("%s", diretorioAprendizado);

  fpAprende = fopen(diretorioAprendizado, "r");

  while(fpAprende == NULL) {
    printf("Não é possivel ler o arquivo, redigite o nome do arquivo");
    scanf("%s", diretorioAprendizado);
    fpAprende = fopen(diretorioAprendizado, "r");
  }

  printf("Valores iniciais %d %d\n", pesos[0], pesos[1]);

  while( contadorExterno <= 100 ) {
    printf("Epoca: %d\n", contadorExterno);

    int contadorInterno = 0;
    do {

      printf("Posiçao dentro do while %d", contadorInterno);

      fgets(string, 14, fpAprende);
      fscanf(fpAprende, "%f;%f;%f", &vetorLinhaTemporario[0], &vetorLinhaTemporario[1], &vetorLinhaTemporario[2]);

      int cont;
      for ( cont = 0; cont < 2; cont++ ) {
        valorAprendido += pesos[cont] * vetorLinhaTemporario[cont];
      }
      valorAprendido = valorAprendido > 0 ? 1 : 0;

      erro = vetorLinhaTemporario[2] - valorAprendido;

      for ( cont = 0; cont < 2; cont++ ) {
        pesos[cont] = pesos[cont] + ( alfa * erro * vetorLinhaTemporario[cont] );
      }

      contadorInterno++;

    } while (!feof(fpAprende));

    contadorExterno++;
  }
  
  fclose(fpAprende);


  return 0;
}


//Funções

int retornaAleatorio() {

  srand(time(NULL));

  return (rand() % 9);

}