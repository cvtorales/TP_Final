#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "common.h"

status_t strdup(const char *sc, char **p)
{
	size_t l;
	/*char * s;*/
	if(sc==NULL)
	{
		return ST_ERROR_PUNTERO_NULO;
	}
	l=strlen(sc)+1;
	if(((*p)=(char*)malloc(sizeof(char)*l))==NULL)
	{
		return ST_ERROR_NO_MEM;
	}
	memcpy(*p,sc,l);
	return ST_OK;
}

status_t split(const char * cadena, char delimitador, char *** arreglo, size_t *l)
{
	char ** campos;
	size_t n, i;
	char * aux, * q, * linea, delim[2];

	if(cadena == NULL || l == NULL)
		return ST_ERROR_PUNTERO_NULO;

	for(i=0, n=1; cadena[i]; i++) /* cuenta la cantidad de tokens que hay en la cadena */
	{
		if(cadena[i]== delimitador)
		{
			n++;
		}
	} 

	if((campos = (char **) malloc(sizeof(char*)*n)) == NULL) /* crea tantos campos como tokens haya*/
	{
		*arreglo=NULL;
		*l=0;
		return ST_ERROR_NO_MEM;
	}

	if((strdup(cadena,&linea))!=ST_OK)
	{
		free(campos);
		*arreglo= NULL;
		*l=0;
		return ST_ERROR_NO_MEM;
	}
	delim[0]= delimitador;
	delim[1]='\0';

	for(i=0, q=linea; (aux= strtok(q, delim))!=NULL;i++,q=NULL)
	{
		if((strdup(aux,&(campos[i]))) != ST_OK)
		{
			destruir_arreglo_cadenas(&campos, i);
			*arreglo=NULL;
			*l=0;
			return ST_ERROR_NO_MEM;
		}
	}

	free(linea);
	*l=i;
	*arreglo=campos;

	return ST_OK;
}

status_t destruir_arreglo_cadenas(char *** campos, size_t n)
{
	size_t i;

	for(i=0; i<n; i++)
	{
		free((*campos)[i]);
		(*campos)[i]=NULL;
	}
	free(*campos);
	*campos=NULL;

	return ST_OK;
}

void destruir_mensaje(void ** mensaje)
{
	if(mensaje!=NULL);
	free(*mensaje);
	*mensaje=NULL;
}


status_t procesar_datos_de_usuario(FILE * archivo, lista_t * lista)
{

	int n,i, cant_tokens,length,id, aux,length_usr, length_nombre,contador_usuarios,*vector_enteros;	
	size_t cant_campos;
	char line[MAX_STR], mensajes_aux[MAX_STR-10],cadena1[50],cadena2[140];
	char **mensaje_atributos,delimitador; 
	char usuario_aux[MAX_STR];
	char * temp, id_aux[5];
	usuario_t *usr;
	mensaje_t *ptr_mensaje;
	char amigos_aux[MAX_STR], nombre_aux[MAX_STR];
	size_t cant_amigos;
	char **amigos;
	status_t st;

	contador_usuarios = 0;

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

	  		(usr)->id = id;
	  		printf("Imprimo el ID cargado al usr: %d\n",usr->id);
	  	}

	
  	/*****************************************************/	
	/*************** Caso de USUARIO *********************/

      if(strncmp(line, CMP_USUARIO, 1) == 0 )
      {
    
    	if((usr = (usuario_t *)malloc(sizeof(usuario_t))) == NULL)
			return ST_ERROR_NO_MEM;
		usr->mensajes = NULL; /* inicializo en esta parte, porque es donde creo la estructura */
        strncpy(usuario_aux, line + 1, n - 2); /* line+1 saltea el 1er corchete, n-2 copia sin incluir el 1er corchete ni el '\n' final*/
    	usuario_aux[n - 3]='\0'; /* n-3 por los 3 caracteres que saque (los dos [] y el '\n'*/
        puts(usuario_aux);

        length_usr = strlen(usuario_aux);
   		if(((usr)->usuario = (char *)malloc(sizeof(char)*(length_usr+1))) == NULL)
    	return ST_ERROR_NO_MEM;

    	strncpy((usr)->usuario,usuario_aux,length_usr);
   		(usr)->usuario[length_usr] = '\0';

      }

    
    /*****************************************************/	  	
	/*************** Caso de NOMBRE **********************/
    if(strncmp(line, CMP_NOMBRE, 6) == 0 )
    {
    
        strncpy(nombre_aux, line + 9, n - 10); /*line+9 saltea la etiqueta nombre = ,n-10 copia sin incluir dicha etiqueta ni '\n' final*/
    	nombre_aux[n-10]='\0';
        puts(nombre_aux);

        length_nombre = strlen(nombre_aux);
    	if(((usr)->nombre = (char *)malloc(sizeof(char)*(length_nombre+1))) == NULL)
    		return ST_ERROR_NO_MEM;

    	strncpy((usr)->nombre,nombre_aux,length_nombre);
    	(usr)->nombre[length_nombre] = '\0';

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
	    if((vector_enteros = malloc(sizeof(int)*cant_amigos)) == NULL)
	    	return ST_ERROR_NO_MEM;
	    for(i=0;i<cant_amigos;i++)
	    {
	      printf("%s\n",amigos[i]);


	     	aux = strtol(amigos[i], &temp, 10);
	  		if( *temp && *temp != '\n')
	  		{
	  			fclose(archivo);

	  			return ST_ERROR_VALIDACION_ID;
	  		}

	  		vector_enteros[i] = aux;
	  	}
	  		/*(usr)->id = id;*/
	  		/*printf("Imprimo el ID cargado al usr: %d\n",usr->id);*/
	  	if((st = TDA_Vector_amigos_cargar(&(usr->amigos), cant_amigos, vector_enteros)) != ST_OK)
  		{
  		TDA_Vector_amigos_destruir(&(usr->amigos));

  		return st; 	
  		}
  		free(vector_enteros);
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

		  	/* Creo la lista de mensajes */
		  	if((usr->mensajes) == NULL)
		  		TDA_Lista_crear(&(usr->mensajes));
		  	/* ************************* */

		  	/* Creo la estructura mensaje_t */
		  	if((ptr_mensaje = (mensaje_t *)malloc(sizeof(mensaje_t))) == NULL)
		  		return ST_ERROR_NO_MEM;

		  	strcpy(ptr_mensaje->str_mensaje,cadena2); /* copio el mensaje util */
		  	strcpy(ptr_mensaje->str_time,mensaje_atributos[1]); /* copio la fecha como string */
		  	aux = strtol(mensaje_atributos[0], &temp, 10); /* copio el id de mensaje */ 
	  		if( *temp && *temp != '\n')
	  		{
	  			return ST_ERROR_VALIDACION_ID;
	  		}

	  		ptr_mensaje->id_mensaje = aux;

	  		aux = strtol(mensaje_atributos[2], &temp, 10); /* copio el id de usuario */ 
	  		if( *temp && *temp != '\n')
	  		{
	  			return ST_ERROR_VALIDACION_ID;
	  		}

	  		ptr_mensaje->id_usuario = aux;
	  		/* ***************************** */
	  		TDA_Lista_insertar_ppio(&(usr->mensajes),(void*)ptr_mensaje);

		  	destruir_arreglo_cadenas(&mensaje_atributos,cant_campos);
  	}
  	/********************************************************/
  	if(line[0] == '\n')
  	{
  		TDA_Lista_insertar_ppio(lista,(void*)usr);
  		contador_usuarios++;
  	}

	}TDA_Lista_insertar_ppio(lista,(void*)usr);
	contador_usuarios++;

	printf("Cantidad de usr: %d\n",contador_usuarios );

	return ST_OK;
}

status_t eliminar_usuarios_por_id(char * delete_id, nodo_t * red)
{
	
	
	if( delete_id == NULL || red == NULL)
		return ST_ERROR_PUNTERO_NULO;
	
	TDA_Lista_recorrer3(red,&eliminar_usuario_por_id,(void *)delete_id);

	return ST_OK;
}

void eliminar_usuario_por_id(void** dato1,void * delete_id)
{
	usuario_t * usr;

 	int cmp;
 	int aux;
 	char * id_aux;
 	char * temp;

 	 id_aux = (char*)delete_id; 
  usr = (usuario_t*)(*dato1);   
	
	if(!dato1 || !delete_id)
		return;
    
    aux = strtol(id_aux, &temp, 10);
    if( *temp && *temp != '\n')
      	return;
	
	if((cmp=comparar_usuarios_por_id(usr,&aux))==0) /* los id son iguales */
		return;

	if((cmp=comparar_usuarios_por_id(usr,&aux))==1)
	{
		destruir_usuario(*dato1);
	}

	return;
}	

status_t  TDA_Lista_recorrer3(lista_t lista, void(*pf)(void**,void*),void*arg)
{
	if(lista==NULL||pf==NULL)
		return ST_ERROR_PUNTERO_NULO;

	while(lista!=NULL)
	{
		(*pf)(&(lista->dato),arg);
		lista=lista->sig;
	}
	return ST_OK;
}

int comparar_usuarios_por_id(void *dato1,void *dato2)
{
	usuario_t *usr1;
	int * id;
	id = (int*)dato2; 
	usr1 =(usuario_t *)dato1;

	if(usr1->id == *id) /*si los id son iguales devuelve 0*/
		return 0;
	return 1; /* si los id son diferentes devuelve 1*/
}