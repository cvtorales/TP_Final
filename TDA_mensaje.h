typedef struct nodo{
						struct nodo * sig;
						void * dato;
					}nodo_t, * lista_t;

typedef enum{TRUE=0,FALSE=1} bool_t;
typedef enum{ST_ERROR_PUNTERO_NULO,ST_ERROR_MEMORIA_INSUFICIENTE,ST_OK} status_t;

bool_t   TDA_Lista_vacios(lista_t);
status_t TDA_Lista_crear(lista_t *);
status_t TDA_Lista_crear_nodo(nodo_t **, void *);
status_t TDA_Lista_destruir_nodo(nodo_t **, void (*)(void *));
status_t TDA_Lista_destruir(lista_t *, void(*)(void *));
status_t TDA_Lista_insertar_ppio (lista_t *, void *);
void * TDA_Lista_buscar(lista_t plista, void *t, int(*cmp)(void*,void*));
status_t TDA_Lista_recorrer(lista_t lista, void(*pf)(void*,void*),void*arg);
status_t TDA_Lista_recorrer2(lista_t lista, void(*pf)(void*));
void imprimir(int *);
nodo_t * TDA_Lista_siguiente(nodo_t * nodo);

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
		ST_ERROR_MEMORIA_INSUFICIENTE;

	(* pnodo)-> sig = NULL;
	(* pnodo)-> dato = dato;

	return ST_OK;

}

status_t TDA_Lista_destruir_nodo(nodo_t **pnodo, void (*destructor)(void *))
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

status_t TDA_Lista_destruir(lista_t * plista, void(*destructor)(void *))
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

void * lista_buscar(lista_t plista, void *t, int(*cmp)(void*,void*))
{
	if(plista==NULL||cmp==NULL)
		return NULL;

	while(plista!=NULL && !(*cmp)(t,plista->dato))
		plista=plista->sig;

	return (plista==NULL)?NULL: plista->dato;
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

void imprimir(int *dato)
{
    printf("%d\n",*dato);
}
