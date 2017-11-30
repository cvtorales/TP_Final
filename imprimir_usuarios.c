#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "funciones.c"

#include "TDA_lista.c"

#define MAX_STR 200
#define CMP_MENSAJES "mensaje"
#define CMP_NOMBRE_ID "id"
#define CMP_USUARIO "["
#define CMP_USUARIO_DELIMITADOR "]"
#define CMP_AMIGOS "amigos"
#define CMP_NOMBRE "nombre"

status_t cargar_archivo_salida(FILE * archivo, nodo_t* red);
status_t imprimir_usuarios(void* red);

int main (void)
{

	FILE * entrada;
  	FILE * salida;
  	archivo = fopen("usuarios.txt","rt");
  	archivo = fopen("salida.txt","wt");
  	status_t st;
  	lista_t lista;
  	
  	/*lista = NULL;*/
  	


	TDA_Lista_crear(&lista);
  	if((st = procesar_datos_de_usuario(entrada, &lista)) != ST_OK)
  	{
  		puts("Error en la funcion procesar datos");
  		/*destruir_usuario(&ptr_usr); HAY QUE DESTRUIR LA LISTA */
  		return EXIT_FAILURE;
  	}

  	puts("Usuarios cargados");
  	/*printf("ID: %d\nNombre: %s\nUsername: %s\n",ptr_usr->id,ptr_usr->nombre,ptr_usr->usuario );
  	destruir_usuario(&ptr_usr);*/
  	

  	FILE * archivo;
  	archivo = fopen("salida.txt","wt");


  	if((cargar_archivo_salida(salida,lista))!=ST_OK);	

	fclose(entrada);
  	fclose(salida);
  	
  
	
	return EXIT_SUCCESS;
}


status_t cargar_archivo_salida(FILE ** archivo, nodo_t * red)
{
	
	
	if(!archivo || !red)
		return ERROR_PUNTERO_NULO;

	TDA_Lista_recorrer2(red,(void*)imprimir_usuarios);

	


	return ST_OK;
}

status_t imprimir_usuarios(void* red)
{
	usuario_t * usr;

	if(!red)
		return ERROR_PUNTERO_NULO

	usr=red->dato; /* usr es un puntero a una estructura de un usuario */
	fprintf(*archivo,"CMP_USUARIO %s CMP_USUARIO_DELIMITADOR'\n'",usr->usuario);

	return ST_OK;
}