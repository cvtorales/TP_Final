#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#include "common.h"
#include "funciones.c"

#define MAX_STR 200
#define CMP_MENSAJES "mensaje"
#define CMP_NOMBRE_ID "id"
#define CMP_USUARIO "["
#define CMP_AMIGOS "amigos"
#define CMP_NOMBRE "nombre"

status_t procesar_datos_de_usuario(FILE * archivo);

int main (void)
{

  	FILE * archivo;
  	archivo = fopen("usuarios.txt","rt");


  	procesar_datos_de_usuario(archivo);	

  	fclose(archivo);
  	
  
	
	return EXIT_SUCCESS;
}





status_t procesar_datos_de_usuario(FILE * archivo)
{

	int n,i, cant_tokens,length,id, aux;
/*	char line[MAX_STR];
*/	
	size_t cant_campos;
	char line[MAX_STR], mensajes_aux[MAX_STR-10],cadena1[50],cadena2[140];
	char **mensaje_atributos,delimitador; 
	char usuario_aux[MAX_STR];
	char * temp, id_aux[5];

	char amigos_aux[MAX_STR], nombre_aux[MAX_STR];
	size_t cant_amigos;
	char **amigos;

	while(fgets(line, MAX_STR ,archivo ) != NULL)
	{
		n = strlen(line);
	
    /*****************************************************/	
	/*************** Caso de ID **************************/
	if(strncmp(line, CMP_NOMBRE_ID, 2) == 0 )
  		{
  	
  			strncpy(id_aux, line + 5, n - 4);
  		
				
											line[n-1]='\0';
  			puts(id_aux);

	  		aux = strtol(id_aux, &temp, 10);
	  		if( *temp && *temp != '\n')
	  		{
	  			fclose(archivo);

	  			return ST_ERROR_VALIDACION_ID;
	  		}

	  		id=aux;
	  		printf("%d\n",id );
	  	}
  	/*****************************************************/	
	/*************** Caso de USUARIO *********************/

      if(strncmp(line, CMP_USUARIO, 1) == 0 )
      {
    
        strncpy(usuario_aux, line + 1, n - 2);
        for(i=0; i < n ;i++)
        {
        	if(usuario_aux[i]==']')
    	    	usuario_aux[i]='\0';
    	}
        puts(usuario_aux);

      }  
    /*****************************************************/	  	
	/*************** Caso de NOMBRE **********************/
      if(strncmp(line, CMP_NOMBRE, 6) == 0 )
      {
    
        strncpy(nombre_aux, line + 9, n - 8);

        puts(nombre_aux);

      } 


    /*****************************************************/	
    /*************** Caso de AMIGOS **********************/
    if(strncmp(line, CMP_AMIGOS, 6) == 0 )
  	{
  		strncpy(amigos_aux,line+9, n - 8);
	   
	     /*line[n-1]='\0';*/
	    puts(amigos_aux);

	    

	 /*   aux = strtol(amigos_aux, &temp, 10);
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

  	}
  	/*****************************************************/	
	/*************** Caso de MENSAJES ********************/

	if(strncmp(line, CMP_MENSAJES, 7) == 0 )
  	{
  		strncpy(mensajes_aux,line+10, n - 9);

  		  	 puts(mensajes_aux);
  			 delimitador = ',';
  			length=0;
    		for(i=0,cant_tokens=0; mensajes_aux[i] && cant_tokens<3; i++) 
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
		    cadena2[n-length]='\0';
		    puts(cadena1);
		    puts(cadena2);
		  	split(cadena1,delimitador,&mensaje_atributos,&cant_campos);
		  	for(i=0;i<cant_campos;i++)
		  	{
		  		printf("%s\n",mensaje_atributos[i]);
		  	}
		  	destruir_arreglo_cadenas(&mensaje_atributos,cant_campos);
  	}
  	/********************************************************/

	}


	return ST_OK;
}