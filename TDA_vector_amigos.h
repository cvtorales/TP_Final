#ifndef TDA_VECTOR_AMIGOS_H
#define TDA_VECTOR_AMIGOS_H

typedef struct
{
	size_t used_size;
	size_t alloc_size;
	int * amigos;
}TDA_vector_s;

#endif
/********************* PROTOTIPOS *************************************************/
status_t TDA_Vector_amigos_crear(TDA_vector_s ** vector);
status_t TDA_Vector_amigos_cargar(TDA_vector_s ** vector, int l, int * dato);
status_t TDA_Vector_amigos_destruir(TDA_vector_s ** vector);
/**********************************************************************************/
