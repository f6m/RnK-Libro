/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 7.1 */

/* El siguiente programa crea una funcion que convierte las may<->min de la Entrada segun la bandera enviada en argv[0] 
Usando tolower/toupper 
prog -l 
prog -u */

/* obs1:
si recorremos ++argv[1] inpseccionando cada caracter del apuntador
cuando referenciamos a ++argv (que seria a argv[1]) nos posiciona donde dejamos su apuntador
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  int c;
  char *f=argv[1];
 if(*argv[1] == '-' && argc==2){
	if(*++argv[1] == 'u'  && *++argv[1]=='\0') //-u\0
	{
	printf("Bandera a procesar 1: %s\n",f); //fue recorrido el apuntador argv[1], explicar como observacioin
	while((c=getchar())!=EOF)
	putchar(toupper(c));
	}
	else if(*(++f) == 'l'  && *(++f)=='\0') //-l\0
	{
	printf("Bandera a procesar 2: %s\n",*++argv);
	while((c=getchar())!=EOF)
	putchar(tolower(c));
	}
	else printf("bandera desconocida %s\n",*++argv);
}else printf("error de sintaxis o demasiados argumentos\n");
 return 0;
}
