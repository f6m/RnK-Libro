/* El lenguaje de programacion C, R&K, (Prentic Hall, 2da. edicion, 1991) */
/* # 1.2 */

/* Programa que muestra los distintos caracteres de espaciado en printf \c \t
\b \\ \" \n */

#include<stdio.h>

int main(){

  printf("Hola \t");
  printf("H \n");
  printf("without fea\br...\b....never\x");
  printf("Amar las pazes como medio para nuevas guerras\\");
  printf("Y amar las pazes cortas mas que las largas \"\n");
}

