/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.4 */

/* Programa que busca la la incidencia de la cadena t al final de la cadena s y  regresa 0 en caso negativo y 1 en caso afirmativo */

#include <stdio.h>
#include <stdlib.h>


int strlen(char *);
void strcpy(char *, char *);
int strcmp(char *, char *);
int strend(char *, char *);
     main(){
  char string[ ]="Feliz Navidad a todos y bienvenido el 2007",*p;
  char cadena[' '];
  p = string;
  printf("La cadena %s tiene longitiud %i\n",string,strlen(p));
  strcpy(cadena,p);
  printf("El contenido de cadena es: %s\n",cadena);
  printf("El resultado de strend(cadena,2007) es %i\n",strend(cadena,"2007"));
}

int strlen(char *s){
  int n;
  for(n=0;*s != '\0';s++)
    n++;
  return n;
}

void strcpy(char *s, char *t){
  while(*s++ = *t++)
    ;
}

int strcmp(char *s, char *t){
  for(;*s == *t;s++,t++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}

int strend(char *s, char *t){
  int i,j;
  i =strlen(t);
  j =strlen(s);
  if (i > j)
    printf("Error: Patron de busqueda mayor que la cadena\n");
  /* Tambien puede hacerse utilizando este ciclo for(i = strlen(t),s[j]==t[i];i--,j--)*/
  while(*(t+(i-1))==*(s+(j-1))){
   --i;
   --j;}
  if(i==0) return 1;
  else return 0;
}


