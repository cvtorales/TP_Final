#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_USER_NAME  40

int main (void)
{
	
	int n;
	char line[MAX_STR_USER_NAME];
  FILE * archivo;
  archivo = fopen("usuario.txt","rt");
  	
  	fseek(archivo, 1, SEEK_CUR);
	fgets(line, MAX_STR_USER_NAME ,archivo );
  	puts(line);

  	n = strlen(line);
  	line[n-1]='\0';
  	  	puts(line);
  	fclose(archivo);
	
	return EXIT_SUCCESS;
}