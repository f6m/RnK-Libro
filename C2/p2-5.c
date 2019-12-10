/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.5 */

/* Programa que dadas dos cadenas s1,s2 regresa el indice/posicion dentro
   del arreglo s1 mostrando la primera incidencia de un caracter de s2, 
   regresa -1 si no encuentra alguno */

#include <stdio.h>
#include <string.h>

/* Declaracion de la funcion */

void any(void);

/* Variables globales, que pueden accesar (mediante extern en otro archivo) cualquier funcion*/

char s1[]="Omar";
char s2[]="hOla";

main()
{

  int c,max1,max2,i=0,j=0;
  printf("Buscar ocurrencias de los caracteres de %s en %s\n",s2,s1);
  any();

  return 0;
}

void any(void){

  int i,j,k;

  extern char s1[];
  extern char s2[];
  printf("Cadena 1:%s\n",s1);
  printf("Cadena 2:%s\n",s2);
  
  for(i=j=0;i<strlen(s1)-1;j++){
    while(s1[j]!=s2[i] && i<strlen(s2)-1)
    {
      i++;
    }
    if(tolower(s1[j])==tolower(s2[i]))
    {
      printf("Ocurrencia de %c en %s posicion %i\n",s2[i],s1,j);
      return;
    }
    i=0;
  } /* for */
} /* any */
