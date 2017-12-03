
#include "TDA_lista.h"
/********************* PROTOTIPOS *************************************************/

status_t split(const char * cadena, char delimitador, char *** arreglo, size_t *l);
status_t strdup(const char*sc, char **p);
status_t destruir_arreglo_cadenas(char *** campos, size_t n);
status_t split_message(const char * cadena, char delimitador, char *** arreglo, size_t *l, int cant_campos);
void destruir_mensaje(void ** mensaje);
status_t procesar_datos_de_usuario(FILE * archivo, lista_t * lista);

/**********************************************************************************/


