#include "TDA_vector_amigos.h"

#define MAX_STR_MENSAJE 140
#define MAX_STR_TIME 11

#ifndef TDA_LISTA_H
#define TDA_LISTA_H

typedef struct nodo{
						struct nodo * sig;
						void * dato;
					}nodo_t, * lista_t;


typedef char* t_cadena;


typedef struct{
				int id_mensaje;
				char str_time[MAX_STR_TIME];
				int id_usuario;
				char str_mensaje[MAX_STR_MENSAJE];
} mensaje_t;

typedef struct{
				int id;
				t_cadena nombre;
				t_cadena usuario;
				TDA_vector_s *amigos;
				lista_t mensajes;
} usuario_t;

typedef enum{TRUE=0,
			 FALSE=1} bool_t; 
#endif
bool_t   TDA_Lista_vacios(lista_t);
status_t TDA_Lista_crear(lista_t *);
status_t TDA_Lista_crear_nodo(nodo_t **, void *);
status_t TDA_Lista_destruir_nodo(nodo_t **, status_t (*)(void *));
status_t TDA_Lista_destruir(lista_t *, status_t(*)(void *));
status_t TDA_Lista_insertar_ppio (lista_t *, void *);
status_t TDA_Lista_insertar_final(lista_t * plista, void * dato);
void * TDA_Lista_buscar(lista_t plista, void *t, int(*cmp)(void*,void*));
int comparar_usuarios_por_id(void *dato1,void *dato2);
status_t TDA_Lista_recorrer(lista_t lista, void(*pf)(void*,void*),void*arg);
status_t TDA_Lista_recorrer2(lista_t lista, void(*pf)(void*));
void imprimir(void *);
void imprimir_mensajes(void *);
nodo_t * TDA_Lista_siguiente(nodo_t * nodo);
void destruir_cadena (void *dato);
status_t destruir_usuario(void *dato);
status_t destruir_struct_mensaje(void *dato);

