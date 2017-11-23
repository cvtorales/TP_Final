#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_ID  40
#define CMP_NOMBRE_ID "id"

int main (void)
{
	
	int n,id,aux;
	char * temp;
	char line[MAX_STR_ID], id_aux[MAX_STR_ID];
  	FILE * archivo;
  	archivo = fopen("id.txt","rt");

	fgets(line, MAX_STR_ID ,archivo );
  	puts(line);

  	n = strlen(line);
  	if(strncmp(line, CMP_NOMBRE_ID, 2) == 0 )
  	{
  		strncpy(id_aux,line+5, n - 4);
  	}


  	/*line[n-1]='\0';*/
  	puts(id_aux);

  	aux = strtol(id_aux, &temp, 10);
  	if( *temp && *temp != '\n')
  	{
  		fclose(archivo);

  		return EXIT_FAILURE;
  	}
  	fclose(archivo);
  	id=aux;
  	printf("%d\n",id );
	
	return EXIT_SUCCESS;
}