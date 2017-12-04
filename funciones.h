
#include "TDA_lista.h"
/********************* PROTOTIPOS *************************************************/

status_t split(const char * cadena, char delimitador, char *** arreglo, size_t *l);
status_t strdup(const char*sc, char **p);
status_t destruir_arreglo_cadenas(char *** campos, size_t n);
status_t split_message(const char * cadena, char delimitador, char *** arreglo, size_t *l, int cant_campos);
void destruir_mensaje(void ** mensaje);
status_t procesar_datos_de_usuario(FILE * archivo, lista_t * lista);

status_t eliminar_usuarios_por_id(char * delete_id, nodo_t * red);
void eliminar_usuario_por_id(void** dato1,void * delete_id);
status_t eliminar_usuarios_por_nombre_usuario(char * delete_usrname, nodo_t * red);
status_t  TDA_Lista_recorrer3(lista_t *lista, int(*pf)(void*,void*),void *delete_id);
status_t  TDA_Lista_recorrer4(lista_t lista, int(*pf)(void*,void*),void *delete_usrname);
status_t destruir_usuario2(void *dato);

/**********************************************************************************/


