#ifndef COMMON_H
#define COMMON_H

typedef enum {

				ST_OK,
				ST_ERROR_NO_MEM,
				ST_ERROR_PUNTERO_NULO,
				ST_ERROR_VALIDACION_ID,
				ST_ERROR_CANT_ARG,
				ST_ERROR_APERTURA_ARCHIVO,
				ST_ERROR_CANTIDAD_INVALIDA_DE_ARGUMENTOS,
 				ST_ERROR_MEMORIA_INSUFICIENTE,
 				ST_ERROR_ARGUMENTO_OPCION,
 				ST_ERROR_ARGUMENTO_FILTRO,
 				ST_ERROR_ARGUMENTO_SALIDA



	/*****************************************************************/			
			} status_t;


#endif

#define MAX_STR 200
#define CMP_MENSAJES "mensaje"
#define CMP_NOMBRE_ID "id"
#define CMP_USUARIO "["
#define CMP_USUARIO_DELIMITADOR "]"
#define CMP_AMIGOS "amigos"
#define CMP_NOMBRE "nombre"

#define	CMD_POS_ID 2
