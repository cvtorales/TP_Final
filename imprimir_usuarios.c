#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "funciones.c"

#include "TDA_lista.c"

#define MAX_STR 200
#define CMP_MENSAJES "mensaje"
#define CMP_NOMBRE_ID "id"
#define CMP_USUARIO "["
#define CMP_USUARIO_DELIMITADOR "]"
#define CMP_AMIGOS "amigos"
#define CMP_NOMBRE "nombre"

status_t cargar_archivo_salida(FILE ** archivo, nodo_t* red);
void imprimir_usuarios(void* red,void *salida);
status_t procesar_datos_de_usuario(FILE * archivo, lista_t * lista);

int main (void)
{

	FILE * entrada;
  	FILE * salida;
  	status_t st;
  	lista_t lista;
    entrada = fopen("usuarios.txt","rt");
    salida = fopen("salida.txt","wt");
  	
  	/*lista = NULL;*/
  	


	TDA_Lista_crear(&lista);
  	if((st = procesar_datos_de_usuario(entrada, &lista)) != ST_OK)
  	{
  		puts("Error en la funcion procesar datos");
  		/*destruir_usuario(&ptr_usr); HAY QUE DESTRUIR LA LISTA */
  		return EXIT_FAILURE;
  	}

  	puts("Usuarios cargados");
  	/*printf("ID: %d\nNombre: %s\nUsername: %s\n",ptr_usr->id,ptr_usr->nombre,ptr_usr->usuario );
  	destruir_usuario(&ptr_usr);*/
  	
    TDA_Lista_recorrer2(lista, &imprimir);

  	if((cargar_archivo_salida(&salida,lista))!=ST_OK);	

	       fclose(entrada);
  	
  fclose(salida);
  fclose(entrada);
  TDA_Lista_destruir(&lista, &destruir_usuario);
	
	return EXIT_SUCCESS;
}


status_t cargar_archivo_salida(FILE ** archivo, nodo_t * red)
{
	
	
	if(!archivo || !red)
		return ST_ERROR_PUNTERO_NULO;

	TDA_Lista_recorrer(red,&imprimir_usuarios,(void*)(*archivo));

	


	return ST_OK;
}

void imprimir_usuarios(void* dato,void *salida)
{
	usuario_t * usr;
  FILE *aux;

  aux = (FILE*)salida;
  usr = (usuario_t*)dato;
	if(!dato)
		return;
     /* usr es un puntero a una estructura de un usuario */
	fprintf(aux,"[%s]\n",usr->usuario);

}

status_t procesar_datos_de_usuario(FILE * archivo, lista_t * lista)
{

  int n,i, cant_tokens,length,id, aux,length_usr, length_nombre,contador_usuarios;
/*  char line[MAX_STR];
*/  
  size_t cant_campos;
  char line[MAX_STR], mensajes_aux[MAX_STR-10],cadena1[50],cadena2[140];
  char **mensaje_atributos,delimitador; 
  char usuario_aux[MAX_STR];
  char * temp, id_aux[5];
  usuario_t *usr;
  char amigos_aux[MAX_STR], nombre_aux[MAX_STR];
  size_t cant_amigos;
  char **amigos;

  contador_usuarios = 0;

  while(fgets(line, MAX_STR ,archivo ) != NULL)
  {
    n = strlen(line);

    


  
    /*****************************************************/ 
  /*************** Caso de ID **************************/
  if(strncmp(line, CMP_NOMBRE_ID, 2) == 0 )
      {
    
        strncpy(id_aux, line + 5, n - 4);
      
      line[n-1]='\0';
        puts(id_aux);

        aux = strtol(id_aux, &temp, 10);
        if( *temp && *temp != '\n')
        {
          fclose(archivo);

          return ST_ERROR_VALIDACION_ID;
        }

        id=aux;
        printf("%d\n",id );

        (usr)->id = id;
        printf("Imprimo el ID cargado al usr: %d\n",usr->id);
      }

  
    /*****************************************************/ 
  /*************** Caso de USUARIO *********************/

      if(strncmp(line, CMP_USUARIO, 1) == 0 )
      {
    
      if((usr = (usuario_t *)malloc(sizeof(usuario_t))) == NULL)
      return ST_ERROR_NO_MEM;
        strncpy(usuario_aux, line + 1, n - 2); /* line+1 saltea el 1er corchete, n-2 copia sin incluir el 1er corchete ni el '\n' final*/
      usuario_aux[n - 3]='\0'; /* n-3 por los 3 caracteres que saque (los dos [] y el '\n'*/
        puts(usuario_aux);

        length_usr = strlen(usuario_aux);
      if(((usr)->usuario = (char *)malloc(sizeof(char)*(length_usr+1))) == NULL)
      return ST_ERROR_NO_MEM;

      strncpy((usr)->usuario,usuario_aux,length_usr);
      (usr)->usuario[length_usr] = '\0';

      }

    
    /*****************************************************/     
  /*************** Caso de NOMBRE **********************/
    if(strncmp(line, CMP_NOMBRE, 6) == 0 )
    {
    
        strncpy(nombre_aux, line + 9, n - 10); /*line+9 saltea la etiqueta nombre = ,n-10 copia sin incluir dicha etiqueta ni '\n' final*/
      nombre_aux[n-10]='\0';
        puts(nombre_aux);

        length_nombre = strlen(nombre_aux);
      if(((usr)->nombre = (char *)malloc(sizeof(char)*(length_nombre+1))) == NULL)
        return ST_ERROR_NO_MEM;

      strncpy((usr)->nombre,nombre_aux,length_nombre);
      (usr)->nombre[length_nombre] = '\0';

    } 

    


    /*****************************************************/ 
    /*************** Caso de AMIGOS **********************/
    if(strncmp(line, CMP_AMIGOS, 6) == 0 )
    {
      strncpy(amigos_aux,line+9, n - 8);
     
       /*line[n-1]='\0';*/
      puts(amigos_aux);

      

   /*   aux = strtol(amigos_aux, &temp, 10);
      if( *temp && *temp != '\n')
      {
        fclose(archivo);

        return EXIT_FAILURE;
      }*/
      delimitador = ',';
      split(amigos_aux,delimitador,&amigos,&cant_amigos);
      for(i=0;i<cant_amigos;i++)
      {
        printf("%s\n",amigos[i]);
      }
      destruir_arreglo_cadenas(&amigos,cant_amigos);

    }
    /*****************************************************/ 
  /*************** Caso de MENSAJES ********************/

  if(strncmp(line, CMP_MENSAJES, 7) == 0 )
    {
      strncpy(mensajes_aux,line+10, n - 9);

           puts(mensajes_aux);
         delimitador = ',';
        length=0;
        for(i=0,cant_tokens=0; mensajes_aux[i] && cant_tokens<3; i++) 
            {
          if(mensajes_aux[i] == delimitador)
          {
              cant_tokens++;
            }
          length++;
        }
        printf("Longitud hasta que empiece el mensaje util: %d\n",length );
        strncpy(cadena1,mensajes_aux,length);
        cadena1[length-1]='\0';
        n = strlen(mensajes_aux);
        strncpy(cadena2,mensajes_aux+length,n-length);
        cadena2[n-length]='\0';
        puts(cadena1);
        puts(cadena2);
        split(cadena1,delimitador,&mensaje_atributos,&cant_campos);
        for(i=0;i<cant_campos;i++)
        {
          printf("%s\n",mensaje_atributos[i]);
        }
        destruir_arreglo_cadenas(&mensaje_atributos,cant_campos);
    }
    /********************************************************/
    if(line[0] == '\n')
    {
      TDA_Lista_insertar_ppio(lista,(void*)usr);
      contador_usuarios++;
    }

  }
  TDA_Lista_insertar_ppio(lista,(void*)usr);
  contador_usuarios++;

  printf("Cantidad de usr: %d\n",contador_usuarios );

  return ST_OK;
}