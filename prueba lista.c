#include <stdio.h>
#include <stdlib.h>
#include "TDA_mensaje.h"
#include "funciones.h"

int main(void)
{
	lista_t lista;
	nodo_t *nodo;
	char* string="hola";

/* creo lista, creo nodo y apunto la lista al nodo, luego imprimo */
	TDA_Lista_crear(&lista);
    TDA_Lista_crear_nodo(&nodo, &string);
    TDA_Lista_insertar_ppio (&lista,&string);
    TDA_Lista_recorrer2(lista, &imprimir);

/* destruyo el nodo, destruyo la lista, y luego verifico lo hizo */
  TDA_Lista_destruir_nodo(&nodo,&destruir_mensaje);
  TDA_Lista_destruir(&lista, &destruir_mensaje);

    return EXIT_SUCCESS;
}
