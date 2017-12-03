#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TDA_vector_amigos.h"







/*int main (void)
{


  	TDA_vector_s * tda_vector;
  	int *dato;
  	int l, i;
  	l=4;

  	dato = (int*)malloc(sizeof(int)*l);
  	dato[0] = 12;
  	dato[1] = 13;
  	dato[2] = 14;
  	dato[3] = 15;

  	if(TDA_Vector_amigos_cargar(&tda_vector, l, dato) != ST_OK)
  	{
  		TDA_Vector_amigos_destruir(&tda_vector);

  		return EXIT_FAILURE; 	
  	}

  	for(i=0; i < l ; i++)
  	{
  	 	printf("El vector es: %d\n", tda_vector->amigos[i]);
  	}
	
	TDA_Vector_amigos_destruir(&tda_vector);
	free(dato);

	return EXIT_SUCCESS;
}*/

/*
status_t TDA_Vector_amigos_crear(TDA_vector_s ** vector)
{
	if (vector == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	if ((*vector = (TDA_vector_s *) malloc(sizeof(TDA_vector_s)))== NULL)
		return ST_ERROR_NO_MEM;
		
	(*vector) -> used_size = 0;
	(*vector) -> alloc_size = 0;
	(*vector) -> amigos = NULL;
	
	return ST_OK;
}

status_t TDA_Vector_amigos_cargar(TDA_vector_s ** vector, int l, int * dato)
{
	status_t st;
	int i;

	if (vector == NULL)
		return ST_ERROR_PUNTERO_NULO;

	if((st = TDA_Vector_amigos_crear(vector))!=ST_OK)
		return st;

	if (((*vector)-> amigos = (int *) malloc(sizeof(int)*l))== NULL)
	{
		TDA_Vector_amigos_destruir(vector);
		return ST_ERROR_NO_MEM;
	}

	for(i=0; i<l ;i++)
	{
		(*vector)->amigos[i]= dato[i];
	}


	(*vector)-> used_size = l;
	(*vector)-> alloc_size = l;

	return ST_OK;

}

status_t TDA_Vector_amigos_destruir(TDA_vector_s ** vector)
{
		if (vector == NULL)
			return ST_ERROR_PUNTERO_NULO;
		if((*vector)->amigos != NULL)
		{
			free((*vector)->amigos);
			(*vector)->amigos = NULL;
		}

		free(*vector);
		*vector = NULL;

		return ST_OK;
}


*/
status_t TDA_Vector_amigos_crear(TDA_vector_s ** vector)
{
	if (vector == NULL)
		return ST_ERROR_PUNTERO_NULO;
		
	if ((*vector = (TDA_vector_s *) malloc(sizeof(TDA_vector_s)))== NULL)
		return ST_ERROR_NO_MEM;
		
	(*vector) -> used_size = 0;
	(*vector) -> alloc_size = 0;
	(*vector) -> amigos = NULL;
	
	return ST_OK;
}

status_t TDA_Vector_amigos_cargar(TDA_vector_s ** vector, int l, int * dato)
{
	status_t st;
	int i;

	if (vector == NULL)
		return ST_ERROR_PUNTERO_NULO;

	if((st = TDA_Vector_amigos_crear(vector))!=ST_OK)
		return st;

	if (((*vector)-> amigos = (int *) malloc(sizeof(int)*l))== NULL)
	{
		TDA_Vector_amigos_destruir(vector);
		return ST_ERROR_NO_MEM;
	}

	for(i=0; i<l ;i++)
	{
		(*vector)->amigos[i]= dato[i];
	}


	(*vector)-> used_size = l;
	(*vector)-> alloc_size = l;

	return ST_OK;

}

status_t TDA_Vector_amigos_destruir(TDA_vector_s ** vector)
{
		if (vector == NULL)
			return ST_ERROR_PUNTERO_NULO;
		if((*vector)->amigos != NULL)
		{
			free((*vector)->amigos);
			(*vector)->amigos = NULL;
		}

		free(*vector);
		*vector = NULL;

		return ST_OK;
}
