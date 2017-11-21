typedef struct nodo{
						struct nodo * sig;
						void * dato;
					}nodo_t, * lista_t;


bool_t   TDA_Lista_mensajes_vacios(lista_t);
status_t TDA_Lista_mensajes_crear(lista_t *);
status_t TDA_Lista_mensajes_crear_nodo(nodo_t **, void *);
status_t TDA_Lista_mensajes_destruir_nodo(nodo_t **, void (*destructor)(void *));
status_t TDA_Lista_mensajes_destruir(lista_t *, void(*)(void *));


bool_t   TDA_Lista_mensajes_vacios(lista_t mensaje)
{
	l==NULL;     /* tenia esto en mi carpeta, lo copie mal */
}

status_t TDA_Lista_mensajes_crear(lista_t * pmensaje)
{
	if(pmensaje == NULL)
		return ST_ERROR_PUNTERO_NULO;

	*pmensaje = NULL;

	return ST_OK; 
}

status_t TDA_Lista_mensajes_crear_nodo(nodo_t ** pnodo, void * dato)
{
	if(pnodo == NULL)
		return ST_ERROR_PUNTERO_NULO;

	if((*pnodo= (nodo_t *) calloc(1, sizeof(nodo_t)))==NULL)
		ST_ERROR_MEMORIA_INSUFICIENTE;

	(* pnodo)-> sig = NULL;
	(* pnodo)-> dato = dato;

	return ST_OK; 

}

status_t TDA_Lista_mensajes_destruir_nodo(nodo_t **pnodo, void (*destructor)(void *))
{
	if(pnodo == NULL)
		return ST_ERROR_PUNTERO_NULO;

	if(destructor != NULL)
		(*destructor)((*pnodo)->dato);

	(*pnodo)-> dato = NULL;
	(*nodo)-> sig = NULL;

	free(*pnodo);

}
