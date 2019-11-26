/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.7 */

/* Programa que imprime el valor de EOF (-1) = ctrl + d*/

#include <stdio.h>

main(){
  int c;

  c=getchar();
  printf("c = %i \n",c);
}
