/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.3 */

/* Programa que implementa la funcion strcat(s,t) que copia la cadena
  t al final de s usando apuntadores */

#include <string.h>
#include <stdio.h>
#include <stdlib.h> /*para malloc/free */


void strcatp(char *s, char *t);
void strcatp2(char *s, char *t);

main(){

/*char *s;
char *t;

s = (char*) malloc(100*sizeof(char));
t = (char*) malloc(100*sizeof(char));


s="hola";
t="adios";


printf("%s\n",s);
printf("%s\n",t);
*/
char h[20]="holahola";
char k[20]="adiosadios";

printf("%s\n",h);
printf("%s\n",k);


strcatp1(h,k);

printf("%s\n",h);
printf("%s\n",k);
  
/*
free(s);
free(t);
*/
}

void strcatp(char *s, char *t){
  int i,j;
  
  i=0;
  while(*(s+i) != '\0')
    i++;
  j=0;
  while((*(s+(i++)) = *(t+(j++))) != '\0')
    ;
}

void strcatp2(char *s, char *t){
  int i,j;
  
  i=0;
  while(*(s+i) != '\0')
    i++;
  j=0;
  do{
    printf("Indices (i,j)=(%i,%i)\n",i,j);
    *(s+i)=*(t+j);
    i++;
    j++;
  }while(*(t+j) != '\0');
  
}
