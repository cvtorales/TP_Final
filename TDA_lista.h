typedef struct nodo{
						struct nodo * sig;
						void * dato;
					}nodo_t, * lista_t;


typedef char* t_cadena;

typedef struct{
				int id;
				t_cadena nombre;
				t_cadena usuario;
				/*vector_s amigos;
				lista_s mensajes;*/
} usuario_t;

typedef enum{TRUE=0,
			 FALSE=1} bool_t;

typedef enum{ST_ERROR_PUNTERO_NULO,
			 ST_ERROR_MEMORIA_INSUFICIENTE,
			 ST_OK} status_t;

bool_t   TDA_Lista_vacios(lista_t);
status_t TDA_Lista_crear(lista_t *);
status_t TDA_Lista_crear_nodo(nodo_t **, void *);
status_t TDA_Lista_destruir_nodo(nodo_t **, status_t (*)(void *));
status_t TDA_Lista_destruir(lista_t *, status_t(*)(void *));
status_t TDA_Lista_insertar_ppio (lista_t *, void *);
status_t TDA_Lista_insertar_final(lista_t * plista, void * dato);
void * TDA_Lista_buscar(lista_t plista, void *t, int(*cmp)(void*,void*));
status_t TDA_Lista_recorrer(lista_t lista, void(*pf)(void*,void*),void*arg);
status_t TDA_Lista_recorrer2(lista_t lista, void(*pf)(void*));
void imprimir(void *);
nodo_t * TDA_Lista_siguiente(nodo_t * nodo);
void destruir_cadena (void *dato);


