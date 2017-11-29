#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TDA_lista.c"



int main(void)
{
	lista_t lista;
	usuario_t *usr1,*usr2,*usr3;
	char str_nombre[] = "Jorge";
	char str_usuario[] = "Hola Jorge";
	void *resultado;
	

	if((usr1=(usuario_t *)malloc(sizeof(usuario_t))) == NULL)
		return EXIT_FAILURE;

	if((usr1->nombre=(char *)malloc(sizeof(char)*32)) == NULL)
		return EXIT_FAILURE;
	
	if((usr1->usuario=(char *)malloc(sizeof(char)*32)) == NULL)
		return EXIT_FAILURE;

	usr1->id = 2538;
	strcpy(usr1->nombre,str_nombre);
	strcpy(usr1->usuario,str_usuario);

	if((usr2=(usuario_t *)malloc(sizeof(usuario_t))) == NULL)
		return EXIT_FAILURE;

	if((usr2->nombre=(char *)malloc(sizeof(char)*32)) == NULL)
		return EXIT_FAILURE;
	
	if((usr2->usuario=(char *)malloc(sizeof(char)*32)) == NULL)
		return EXIT_FAILURE;

	usr2->id = 2548;
	strcpy(usr2->nombre,str_nombre);
	strcpy(usr2->usuario,str_usuario);

	if((usr3=(usuario_t *)malloc(sizeof(usuario_t))) == NULL)
		return EXIT_FAILURE;

	if((usr3->nombre=(char *)malloc(sizeof(char)*32)) == NULL)
		return EXIT_FAILURE;
	
	if((usr3->usuario=(char *)malloc(sizeof(char)*32)) == NULL)
		return EXIT_FAILURE;

	usr3->id = 2538;
	strcpy(usr3->nombre,str_nombre);
	strcpy(usr3->usuario,str_usuario);
/* creo lista, creo nodo y apunto la lista al nodo, luego imprimo */
	TDA_Lista_crear(&lista);
    /*TDA_Lista_crear_nodo(&nodo, (void*)string);*/
    TDA_Lista_insertar_ppio(&lista,(void*)usr1);
    TDA_Lista_insertar_final(&lista,(void*)usr2);
  

	/*TDA_Lista_insertar_final (&lista,(void*)s);*/
    TDA_Lista_recorrer2(lista, &imprimir);

    resultado = lista_buscar(lista, (void *)usr3, &comparar_usuarios_por_id);

    if(resultado != NULL)
    	imprimir(resultado);

/* destruyo el nodo, destruyo la lista, y luego verifico lo hizo */
/*  TDA_Lista_destruir_nodo(&nodo,&destruir_mensaje); */
    TDA_Lista_destruir(&lista, &destruir_usuario);
    destruir_usuario((void*)usr3);

    return EXIT_SUCCESS;
}
