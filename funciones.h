//int comparar_por_id(usuario *a, usuario *b);
void destruir_mensaje(void ** mensaje);





/*int comparar_por_id(usuario *a, usuario *b)
{
	return b->id - a->id;
} */

void destruir_mensaje(void ** mensaje)
{
	if(mensaje!=NULL);
	free(*mensaje);
	*mensaje=NULL;
}
