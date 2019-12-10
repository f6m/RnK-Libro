/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.5 */

/* Programa que implementa la funcion strcmpn(s,t,n) que copia los n primeros
 * argumentos de la cadena t en la cadena s, esta version usa apuntadores */


#include <string.h>
#include <stdio.h>
#include <stdlib.h> /*para malloc/free */


void strcmpnp(char *s, char *t, int n);

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


strcmpnp(h,k,4);

printf("%s\n",h);
printf("%s\n",k);
  
/*
free(s);
free(t);
*/
}

void strcmpnp(char *s, char *t, int n){
  int i;
  
  i=0;
  do{
    *(s+i) = *(t+i);
    i++;
  }while( i <= n-1);
}

