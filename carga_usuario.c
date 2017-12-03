#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "TDA_lista.c"
#include "funciones.c"
#include "TDA_vector_amigos.c"

status_t cargar_archivo_salida(FILE ** archivo, nodo_t* red);
void imprimir_usuarios(void* red,void *salida);
void imprimir_mensajes_salida(void *dato, void * archivo);

int main (void)
{

  	FILE * archivo;
  	FILE * salida;

  	status_t st;
  	lista_t lista;
  	archivo = fopen("usuarios.txt","rt");
  	salida = fopen("salida.txt","wt");

	TDA_Lista_crear(&lista);
  	if((st = procesar_datos_de_usuario(archivo, &lista)) != ST_OK)
  	{
  		puts("Error en la funcion procesar datos");
  		/*destruir_usuario(&ptr_usr); HAY QUE DESTRUIR LA LISTA */
  		return EXIT_FAILURE;
  	}

  	puts("Usuarios cargados");
  	
  	TDA_Lista_recorrer2(lista, &imprimir);

  	puts("Aca entro a la funcion para imprimir a la salida");
  	cargar_archivo_salida(&salida,lista);

  	fclose(archivo);
  	fclose(salida);
  	TDA_Lista_destruir(&lista, &destruir_usuario);
  	
  
	
	return EXIT_SUCCESS;
}

status_t cargar_archivo_salida(FILE ** archivo, nodo_t * red)
{
	
	
	if( archivo == NULL || red == NULL)
		return ST_ERROR_PUNTERO_NULO;
	printf( "estoy en la funcion para cargar archivos de salida \n");
	TDA_Lista_recorrer(red,&imprimir_usuarios,(void*)(*archivo));

	


	return ST_OK;
}

void imprimir_usuarios(void* dato, void *salida)
{
	usuario_t * usr;
	FILE *aux;
	int i;

	aux = (FILE*)salida;
  	usr = (usuario_t*)dato;
	if(!dato)
		return;
     /* usr es un puntero a una estructura de un usuario */
	fprintf(aux,"%s%s%s\n",CMP_USUARIO, usr->usuario, CMP_USUARIO_DELIMITADOR);
	fprintf(aux,"id = %d\n",usr->id);

    fprintf(aux,"nombre = %s\n",usr->nombre);
  /*  fprintf(aux,"Username: %s\n",aux->usuario);  */
    fprintf(aux,"amigos = ");
    for (i=0; i<(usr->amigos->used_size); i++)
    {
    	if(((usr->amigos->used_size) -1));
    		fprintf(aux,"%d,",usr->amigos->amigos[i]);

    	if(i==((usr->amigos->used_size) -1))
    		fprintf(aux,"%d\n",usr->amigos->amigos[i]);	
    }

    
  TDA_Lista_recorrer(usr->mensajes, &imprimir_mensajes_salida, aux);
  	fprintf(aux,"\n");	
}

void imprimir_mensajes_salida(void *dato, void * archivo)
{
	mensaje_t* aux;

	aux = (mensaje_t *)dato;
	fprintf(archivo, "mensaje = %d,%s,%d,%s",aux->id_mensaje, aux->str_time, aux->id_usuario,aux->str_mensaje);
}