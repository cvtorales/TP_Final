#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "TDA_lista.c"
#include "funciones.c"
#include "TDA_vector_amigos.c"

#define MSJ_ERROR_VALIDACION "Error en la validacion de los argumentos"
#define POSICION_OPCION 1
#define POSICION_FILTRO 2
#define POSICION_SALIDA 3
#define POSICION_ARCHIVO_ENTRADA 5

#define OPCION_ELIMINAR_LARGA "--eliminar"
#define OPCION_ELIMINAR_CORTA "-e"
#define FILTRO_ID 'i'
#define FILTRO_USUARIO 'u'
#define OPCION_SALIDA "-o"
#define MAX_ID_LENGTH 10

status_t cargar_archivo_salida(FILE ** archivo, nodo_t* red);
status_t validar_argumentos(int argc, char *argv[], FILE **fentrada,char **line);
void imprimir_usuarios(void* red,void *salida);
void imprimir_mensajes_salida(void *dato, void * archivo);

int main (int argc, char *argv[])
{

    FILE * archivo;
    FILE * salida;
    char *delete;
    status_t st;
    lista_t lista;

    if((st = validar_argumentos(argc,argv,&archivo,&delete))!=ST_OK)
    {
    fprintf(stderr, MSJ_ERROR_VALIDACION);
    return EXIT_FAILURE;
    }
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
    eliminar_usuarios_por_id(delete,lista);
    puts("Aca entro a la funcion para imprimir a la salida");
    cargar_archivo_salida(&salida,lista);
    free(delete);
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

status_t validar_argumentos(int argc, char *argv[], FILE **fentrada,char **line)
{
  if( !argv )
  {
    return ST_ERROR_PUNTERO_NULO;
  }

  if((strcmp(argv[POSICION_OPCION],OPCION_ELIMINAR_LARGA)) && (strcmp(argv[POSICION_OPCION],OPCION_ELIMINAR_CORTA)) )
  {
    return ST_ERROR_ARGUMENTO_OPCION;
  }

  if((*(argv[POSICION_FILTRO]) != FILTRO_ID) && (*(argv[POSICION_FILTRO]) != FILTRO_USUARIO) ) 
  {
    return ST_ERROR_ARGUMENTO_FILTRO;
  }

  if(*(argv[POSICION_FILTRO]) == FILTRO_ID)
  {
    *line=(char *)malloc(sizeof(char)*(MAX_ID_LENGTH+1));
    strcpy(*line,argv[POSICION_FILTRO]+2);
  }

  if(*(argv[POSICION_FILTRO]) == FILTRO_USUARIO)
  {
    *line=(char *)malloc(sizeof(char)*(MAX_ID_LENGTH+1));
    strcpy(*line,argv[POSICION_FILTRO]+2);
  }

  if((strcmp(argv[POSICION_SALIDA],OPCION_SALIDA)) )
  {
    return ST_ERROR_ARGUMENTO_SALIDA;
  }

  if((*fentrada = fopen(argv[POSICION_ARCHIVO_ENTRADA],"rt"))==NULL)
  {
    return ST_ERROR_APERTURA_ARCHIVO;
  }

  return ST_OK;
}