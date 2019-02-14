#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//  Aqui ficarão os protótipos das funções
float retornaAleatorio();

int main(void) {

  float i, j;
  float pesos[2] = {retornaAleatorio(), retornaAleatorio()};
  float vetorLinhaTemporario[3] = {};
  FILE *fpAprende, *fpTeste;
  char string[14];
  char diretorioAprendizado[500], diretorioTeste[500];
  float valorAprendido = 0;
  float erro = 0;
  float alfa = 0.05;
  float acertoAprendizado = 0;
  float acertoTeste = 0;
  float percentualAprendido = 0;
  float percentualAcertoTeste = 0;

  printf("Digite o caminho do arquivo de aprendizagem: ");
  scanf("%s", diretorioAprendizado);

  printf("Digite o caminho do arquivo de teste: ");
  scanf("%s", diretorioTeste);

  fpAprende = fopen(diretorioAprendizado, "r");
  fpTeste = fopen(diretorioTeste, "r");

  while(fpAprende == NULL) {
    printf("Não foi possivel ler o arquivo de aprendizado , redigite o caminho do arquivo: ");
    scanf("%s", diretorioAprendizado);
    fpAprende = fopen(diretorioAprendizado, "r");
  }
  while(fpTeste == NULL) {
    printf("Não foi possivel ler o arquivo de teste , redigite o caminho do arquivo: ");
    scanf("%s", diretorioTeste);
    fpTeste = fopen(diretorioTeste, "r");
  }

  //Aprendizado
  for ( i = 0; i <= 200; i++ ) {
    if ( i != 0 ) {
      fpAprende = fopen(diretorioAprendizado, "r");
    }
    for( j = 0; !feof(fpAprende); j++ ) {

      fgets(string, 14, fpAprende);
      fscanf(fpAprende, "%f;%f;%f", &vetorLinhaTemporario[0], &vetorLinhaTemporario[1], &vetorLinhaTemporario[2]);
				
      int cont;
      for ( cont = 0; cont < 2; cont++ ) {
        valorAprendido += pesos[cont] * vetorLinhaTemporario[cont];
      }
      valorAprendido = valorAprendido > 0 ? 1 : 0;

      erro = vetorLinhaTemporario[2] - valorAprendido;
      if ( (erro == 0) && (i == 200) ) {
        acertoAprendizado++;
      }

      for ( cont = 0; cont < 2; cont++ ) {
        pesos[cont] = pesos[cont] + ( alfa * erro * vetorLinhaTemporario[cont] );
      }

    }
  }
  percentualAprendido = (acertoAprendizado/(j-1))*100;

  //Teste
  for ( j = 0; !feof(fpTeste); j++ ) {

    fgets(string, 14, fpTeste);
    fscanf(fpTeste, "%f;%f;%f", &vetorLinhaTemporario[0], &vetorLinhaTemporario[1], &vetorLinhaTemporario[2]);

    int cont;
    for ( cont = 0; cont < 2; cont++ ) {
      valorAprendido += pesos[cont] * vetorLinhaTemporario[cont];
    }
    valorAprendido = valorAprendido > 0 ? 1 : 0;

    erro = vetorLinhaTemporario[2] - valorAprendido;
    if (erro == 0) {
      acertoTeste++;
    }

  }
  percentualAcertoTeste = (acertoTeste/(j-1))*100;

  printf("\nPercentual acerto de aprendizagem: %1.2lf%%\n", percentualAprendido);
  printf("\nPercentual acerto de teste: %1.2lf%%\n", percentualAcertoTeste);
  printf("\nValores encontrados para W(Pesos): %f %f\n", pesos[0], pesos[1]);

  fclose(fpAprende);
  fclose(fpTeste);

  return 0;
}

//Funções
float retornaAleatorio() {

  srand(time(NULL));

  return (rand() % 9);

}
