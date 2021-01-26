#include <stdio.h>

/* Programa : Recuperador de fotos JPEG (recover.c)
   Descrição: Este programa recupera fotos jpg em uma partição ou imagem da qual os arquivos tenham sido
              apagados obervando as os seguintes fatos:
	      - Todos os arquivos jpeg começam com os seguintes 3 bytes em hexadecimal:
	          ff, d8, ff
	      - As imagens são de partições de dispositivos microSD de câmeras, cujo sistema de arquivos
	        é fat32. Neste sistema, todos os arquivos são armazenados em blocos de 512 Bytes, mesmo
		que a informação do arquivo tenha um tamanho menor que este.
	      - É assumido que as imagens de partição só tenham as fotos cujos arquivos foram apagados
	      Logo, se o início de qualquer tiver os 3 bytes, isso significa o começo de um novo arquivo
   Autor: Atenágoras Souza Silva
   Data : 13-/08/2018
   Fluxo do Programa:
 */

/* Busca assinatura de inicio de arquivo JPEG (.jpg: 0xff 0xd8 0xff) 
   parâmetros:  stream == pacote de 512 bytes lido de stdin com fread
   Retorna 1 caso encontrado e 0 caso não encontrado */
int JPGfootprint(unsigned char *stream){
  int flag = 0;
  if (stream[0] == 0xff && stream[1] == 0xd8 && stream[2] == 0xff)
    flag = 1;
  else
    flag = 0;
  return flag;
}

/* Grava fotos em caso de êxito 
   retorno: 1 em caso de encontrar ao menos uma imagem, e 0 caso não encontre nenhuma */
int GravaFotos(){
  int flag = 1;
  unsigned char stream[512]; // string para leitura e escrita de 512 bytes da entrada padrão (stdin)
  do{
    fread(stream, sizeof(unsigned char), 512, stdin);
  }while ( !feof(stdin) && !JPGfootprint(stream) ); /* repete se encontrar quaisquer das condições:
						       fim de arquivo; assinatura de JPEG */
  if ( feof(stdin) ){ // Se arquivo de entrada padrão chegou até o fim, é porque não há figura no dispositivo
    flag = 0;
    return flag;
  }
  // Se a função continua depois deste ponto, é porque, de fato, há figuras na imagem
  FILE *saida; // ponteiro para arquivo de saida
  char fnome[8]; // nome do arquivo
  int i = 0; // contador de fotografias recuperadas - útil para nomear arquivo de saída
  while( !feof(stdin) ){
    sprintf(fnome, "%03d.jpg", i);
    saida = fopen(fnome, "wb");
    do{
      fwrite(stream, sizeof(unsigned char), 512, saida);
      fread(stream, sizeof(unsigned char), 512, stdin);
    }while( !feof(stdin) && !JPGfootprint(stream) ); /* repete se encontrar quaisquer das condições:
							fim de arquivo; assinatura de JPEG */
    fclose(saida);
    i++;
  }
  return flag;
}

int main(int argc, char *argv[])
{
  if ( GravaFotos() )
    return 0;// Imagem de microSD contém ao menos uma foto
  else
    printf("Could not find pictures\n");
  //return 1; // Imagem de microSD não contém nenhuma foto
  //return 0;
}
