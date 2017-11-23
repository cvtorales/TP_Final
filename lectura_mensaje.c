#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#include "common.h"
#include "funciones.c"

#define MAX_STR_MENSAJES 200
#define CMP_MENSAJES "mensaje"

int main (void)
{
	
	int n,i, cant_tokens,length;
  size_t cant_campos;
	char line[MAX_STR_MENSAJES], mensajes_aux[MAX_STR_MENSAJES-10],cadena1[50],cadena2[140];
	char **mensaje_atributos,delimitador;
  	FILE * archivo;
  	archivo = fopen("mensaje.txt","rt");

	fgets(line, MAX_STR_MENSAJES ,archivo );
  	puts(line);

  	n = strlen(line);
  	if(strncmp(line, CMP_MENSAJES, 7) == 0 )
  	{
  		strncpy(mensajes_aux,line+10, n - 9);
  	}


  	/*line[n-1]='\0';*/
  	puts(mensajes_aux);

  	

 /* 	aux = strtol(mensajes_aux, &temp, 10);
  	if( *temp && *temp != '\n')
  	{
  		fclose(archivo);

  		return EXIT_FAILURE;
  	}*/
  

  	delimitador = ',';
  	length=0;
    for(i=0,cant_tokens=0; mensajes_aux[i] && cant_tokens<3; i++) /* cuenta longitud de cadena1, que es lo previo al mensaje en si */
    {
      if(mensajes_aux[i] == delimitador)
      {
        cant_tokens++;
      }
      length++;
    }
    printf("Longitud hasta que empiece el mensaje util: %d\n",length );
    strncpy(cadena1,mensajes_aux,length);
    cadena1[length-1]='\0';
    n = strlen(mensajes_aux);
    strncpy(cadena2,mensajes_aux+length,n-length);
    puts(cadena1);
    puts(cadena2);
  	split(cadena1,delimitador,&mensaje_atributos,&cant_campos);
  	for(i=0;i<cant_campos;i++)
  	{
  		printf("%s\n",mensaje_atributos[i]);
  	}
  	destruir_arreglo_cadenas(&mensaje_atributos,cant_campos);
  	fclose(archivo);
  	
  
	
	return EXIT_SUCCESS;
}