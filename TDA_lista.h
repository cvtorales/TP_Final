#include "TDA_vector_amigos.h"

#define MAX_STR_MENSAJE 140
#define MAX_STR_TIME 11

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

bool_t   TDA_Lista_vacios(lista_t lista)
{
	return lista==NULL;
}

status_t TDA_Lista_crear(lista_t * plista)
{
	if(plista == NULL)
		return ST_ERROR_PUNTERO_NULO;

	*plista = NULL;

	return ST_OK;
}

status_t TDA_Lista_crear_nodo(nodo_t ** pnodo, void * dato)
{
	if(pnodo == NULL)
		return ST_ERROR_PUNTERO_NULO;

	if((*pnodo= (nodo_t *) calloc(1, sizeof(nodo_t)))==NULL)
		return ST_ERROR_MEMORIA_INSUFICIENTE;

	(* pnodo)-> sig = NULL;
	(* pnodo)-> dato = dato;

	return ST_OK;

}

status_t TDA_Lista_destruir_nodo(nodo_t **pnodo, status_t (*destructor)(void *))
{
	if(pnodo == NULL)
		return ST_ERROR_PUNTERO_NULO;

	if(destructor != NULL)
		(*destructor)((*pnodo)->dato);

	(*pnodo)-> dato = NULL;
	(*pnodo)-> sig = NULL;

	free(*pnodo);
	*pnodo=NULL;
	return ST_OK;

}

status_t TDA_Lista_destruir(lista_t * plista, status_t (*destructor)(void *))
{
	nodo_t * primero;

	if(plista==NULL)
		return ST_ERROR_PUNTERO_NULO;

	while(*plista!=NULL)
	{
		primero=*plista;
		*plista=(*plista)->sig;
		TDA_Lista_destruir_nodo(&primero,destructor);
	}

	return ST_OK;
}

status_t TDA_Lista_insertar_ppio(lista_t * plista, void * dato)
{
	status_t st; nodo_t *nodo;
	if(plista==NULL)
		return ST_ERROR_PUNTERO_NULO;

	if((st=TDA_Lista_crear_nodo(&nodo,dato))!=ST_OK)
		return st;

	nodo->sig=*plista;
	*plista=nodo;
	return ST_OK;
}

status_t TDA_Lista_insertar_final(lista_t * plista, void * dato)
{
	status_t st; nodo_t *nodo,*aux;
	if(plista==NULL)
		return ST_ERROR_PUNTERO_NULO;

	if((st=TDA_Lista_crear_nodo(&nodo,dato))!=ST_OK)
		return st;

	if(*plista == NULL)
	{
		if((st=TDA_Lista_crear_nodo(&nodo,dato))!=ST_OK)
			return st;
		*plista=nodo;
		return ST_OK;
	}
	aux = *plista;
	
	while(aux->sig != NULL)
		aux = aux->sig;

	aux->sig = nodo;
	
	return ST_OK;
}

void * lista_buscar(lista_t plista, void *t, int(*cmp)(void*,void*))
{
	lista_t aux_recorrer;
	if(plista==NULL||cmp==NULL)
		return NULL;
	aux_recorrer = plista;
	while(aux_recorrer!=NULL && (*cmp)(t,aux_recorrer->dato))
		aux_recorrer=aux_recorrer->sig;

	return (aux_recorrer==NULL)?NULL: aux_recorrer->dato;
}

int comparar_usuarios_por_id(void *dato1,void *dato2)
{
	usuario_t *usr1,*usr2;
	usr1 =(usuario_t *)dato1;
	usr2 =(usuario_t *)dato2;

	if(usr1->id == usr2->id) /*si los id son iguales devuelve 0*/
		return 0;
	return 1; /* si los id son diferentes devuelve 1*/
}

status_t  TDA_Lista_recorrer(lista_t lista, void(*pf)(void*,void*),void*arg)
{
	if(lista==NULL||pf==NULL)
		return ST_ERROR_PUNTERO_NULO;

	while(lista!=NULL)
	{
		(*pf)(lista->dato,arg);
		lista=lista->sig;
	}
	return ST_OK;
}

status_t  TDA_Lista_recorrer2(lista_t lista, void(*pf)(void*))
{
    if(lista==NULL||pf==NULL)
		return ST_ERROR_PUNTERO_NULO;

	while(lista!=NULL)
	{
		(*pf)(lista->dato);
		lista=lista->sig;
	}
	return ST_OK;

}

nodo_t * TDA_Lista_siguiente(nodo_t * nodo)
{
	return nodo->sig;
}

void imprimir(void *dato)
{
	usuario_t* aux;
	int i;
	aux = (usuario_t *)dato;
    printf("ID: %d\n",aux->id);
    printf("Nombre: %s\n",aux->nombre);
    printf("Username: %s\n",aux->usuario);
    printf("Amigos:\n");
    for (i=0;i<(aux->amigos->used_size);i++)
    	printf("%d\n",aux->amigos->amigos[i]);
    TDA_Lista_recorrer2(aux->mensajes, &imprimir_mensajes);
}

void imprimir_mensajes(void *dato)
{
	mensaje_t* aux;
	aux = (mensaje_t *)dato;
	printf("Mensaje_t\n");
	printf("Id mensaje: %d\n",aux->id_mensaje );
	printf("Fecha: %s\n",aux->str_time );
	printf("Id usuario: %d\n",aux->id_usuario );
	printf("Mensaje util: %s\n",aux->str_mensaje );
}

void destruir_cadena (void *dato)
{
	char *cadena;
	cadena =(char *)dato;
	free(cadena);
	cadena = NULL;
}


status_t destruir_struct_mensaje(void *dato)
{
	mensaje_t* mensaje;
	mensaje = (mensaje_t *)dato;

	if(!mensaje)
		return ST_ERROR_PUNTERO_NULO;

	free(mensaje);
	mensaje = NULL;

	return ST_OK;
}

status_t destruir_usuario(void *dato)
{
	usuario_t* usr;
	usr = (usuario_t *)dato;

	if(!usr)
		return ST_ERROR_PUNTERO_NULO;

	if((usr)->usuario)
	{
		free((usr)->usuario);
		(usr)->usuario = NULL;
	}

	if((usr)->nombre)
	{
		free((usr)->nombre);
		(usr)->nombre = NULL;
	}

	TDA_Vector_amigos_destruir(&(usr->amigos));
	TDA_Lista_destruir(&(usr->mensajes),&destruir_struct_mensaje);

	free(usr);
	usr = NULL;

	return ST_OK;
}