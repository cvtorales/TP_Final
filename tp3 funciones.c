#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MENSAJE 140
#define INIT_SIZE 100

typedef char* t_cadena;

typedef struct{
				int id;
				t_cadena nombre;
				t_cadena usuario;
				vector_s amigos;
				lista_s mensajes;
} usuario_t;

typedef enum{ST_OK;
			ST_FAILURE;
			ERR_NULL_PONTER;
			ERR_NO_MEM;
			ERR_CORRUPT_FILE;
			ERR_NULL_FILE;
			} status_t;

usuario_t * cargar_usuario(FILE * archivo ,status_t * st );
void destruir_usuario(usuario_t ** usuario);
status_t destruir_usuarios(usuario_t *** usuarios, size_t * longitud); /* puntero triple porq primero es ** por querer pasar el usuario_t por referencia, el otro * es por ser arreglo */
status_t cargar_usuarios(FILE * archivo, usuario_t ***, size_t * n);			


void destruir_usuario(usuario_t ** usuario)
{
	if(usuario!=NULL);
	free(*usuario);
	*usuario=NULL;
}

status_t destruir_usuarios(usuario_t *** usuarios, size_t * longitud)
{
    size_t i;
    if(!usuario || !longitud)
    {
    	return ERR_NULL_POINTER;
    }
	for(i=0,i<(*longitud),i++)
	{
		destruir_usuario(&(*usuarios)[i]); /* primero entras a los campos con *[i] y luego el & para que te quede bien el *** ya que destruir_usuario(**) */
	}
	free(*usuarios); /* libera el vector */
	*longitud=0; 
	return ST_OK;
}

usuario_t * cargar_usuario(FILE* archivo ,status_t* st )
{
	usuario_t * aux;

	if(!archivo)
	{
		*st=ERR_NULL_FILE;
		return NULL;
	}
	if((aux=(usuario_t*)malloc(sizeof(usuario_t)))==NULL)
	{ 													/*aca pedis memoria para toda la estructura */
		*st=ERR_NO_MEM;
		return NULL;
	}
	
	if(fread(&(aux->id),sizeof(size_t),1,archivo)!=1) /* empezas a leer campo a campo */
	{	
		liberar_usuario(&aux);
		*st=ERR_CORRUPT_FILE;
		return NULL;
	}
	if(fread((aux->nombre),sizeof(size_t),1,archivo)!=1) /* empezas a leer campo a campo */
	{	
		liberar_usuario(&aux);
		*st=ERR_CORRUPT_FILE;
		return NULL;
	}
	
	if(fread((aux->usuario),sizeof(char),l,archivo)!=l) /* seguis leyendo campo a campo */
	{
		liberar_usuario(&aux);
		*st=ERR_CORRUPT_FILE;
		return NULL;
	}	
	

	if(fread((aux->amigos),sizeof(char),1,archivo)!=1) /* seguis leyendo campo a campo no estoy seguro si va & o no cuando es una lista*/
	{
		liberar_usuario(&aux);
		*st=ERR_CORRUPT_FILE;
		return NULL;
	}
	
	if(fread((aux->mensajes),sizeof(double),1,archivo)!=1) /* seguis leyendo campo a campo no estoy seguro si va & o no cuando es una lista*/
	{
		liberar_usuario(&aux);
		*st=ERR_CORRUPT_FILE;
		return NULL;
	}	
	*st=ST_OK;
	return aux;
}

status_t cargar_usuarios(FILE * archivo, usuario_t *** usuarios, size_t * l)
{
	size_t used_size, alloc_size;
	usuario_t **usuario, **aux1,**aux2;

	if(!archivo || !usuarios || !l)
	{
		return ERR_NULL_POINTER;
		*usuarios=NULL;
		*l=0;
	}

    if((usuario=(usuario_t**)malloc(sizeof(usuario_t*)*INIT_SIZE))==NULL)
		return ERR_NO_MEM;

	alloc_size=INIT_SIZE;
	used_size = 0;

	if((cargar_usuario(archivo,&usuario[0])) ==NULL)
	{
		liberar_usuarios(&usuario, &used_size);
		return ST_OK;
	}
	used_size ++;

	while(!feof(archivo))
	{
		if(used_size == alloc_size) /*entra aca cuando se haya llenado la memoria al pedir memoria para vectores (alloc_size) */
		{
			if((aux1 =(usuario_t **)realloc(*usuario,(alloc_size*2)*sizeof(usuario_t *))) == NULL)/*si se pone usuario en vez de aux, si falla usuario es null entonces pierdo el dato*/
			{													/*puedo pedir 100 o otro valor pero en este caso pido el doble (estrategia de crecimiento)*/		
				liberar_usuarios(&usuario,&used_size);
				return ST_ERROR_MEMORIA;
			}
			usuario = aux1;
			alloc_size *=2;
		}


		if((cargar_usuario(archivo,&usuario[used_size]))==NULL) /* aca arranca con pedir memoria */
		{
			liberar_usuarios(&usuario, &used_size)
			return ERR_NULL_POINTER;

		}
		used_size ++;

	}

	if((aux2 = (usuario_t **)realloc(usuario,used_size*sizeof(usuario_t*))) != NULL)
	{
		usuario=aux2;
	}

	else
	{
		return ERR_NO_MEM;
	}

	*usuarios = usuario;
	*l = used_size;
	return ST_OK;
}
