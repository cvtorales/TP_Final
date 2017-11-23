#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#include "common.h"
#include "funciones.c"

#define MAX_STR_AMIGOS 140
#define CMP_AMIGOS "amigos"

int main (void)
{
	
	int n,i;
	size_t cant_amigos;
	char line[MAX_STR_AMIGOS], amigos_aux[MAX_STR_AMIGOS];
	char **amigos,delimitador;
  	FILE * archivo;
  	archivo = fopen("amigos.txt","rt");

	fgets(line, MAX_STR_AMIGOS ,archivo );
  	puts(line);

  	n = strlen(line);
  	if(strncmp(line, CMP_AMIGOS, 6) == 0 )
  	{
  		strncpy(amigos_aux,line+9, n - 8);
  	}


  	/*line[n-1]='\0';*/
  	puts(amigos_aux);

  	

 /* 	aux = strtol(amigos_aux, &temp, 10);
  	if( *temp && *temp != '\n')
  	{
  		fclose(archivo);

  		return EXIT_FAILURE;
  	}*/
  	delimitador = ',';
  	split(amigos_aux,delimitador,&amigos,&cant_amigos);
  	for(i=0;i<cant_amigos;i++)
  	{
  		printf("%s\n",amigos[i]);
  	}
  	destruir_arreglo_cadenas(&amigos,cant_amigos);
  	fclose(archivo);
  	
  
	
	return EXIT_SUCCESS;
}