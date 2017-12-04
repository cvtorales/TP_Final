#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "TDA_lista.c"
#include "funciones.c"
#include "TDA_vector_amigos.c"

int main (int argc, char *argv[])
{

    FILE * archivo;
    FILE * salida;
    char *delete,opcion;
    status_t st;
    lista_t lista;

    if((st = validar_argumentos(argc,argv,&archivo,&delete,&opcion))!=ST_OK)
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


    
    TDA_Lista_recorrer2(lista, &imprimir);
    if(opcion == FILTRO_ID)
      eliminar_usuarios_por_id(delete,lista);
    if(opcion == FILTRO_USUARIO)
      eliminar_usuarios_por_nombre_usuario(delete,lista);

    cargar_archivo_salida(&salida,lista);
    free(delete);
    fclose(archivo);
    fclose(salida);
    TDA_Lista_destruir(&lista, &destruir_usuario);
    
  
  
  return EXIT_SUCCESS;
}
