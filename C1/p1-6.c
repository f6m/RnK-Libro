/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.6 */

/* Programa que verifica que la expresion getchar() != EOF es 0 o 1 dependiendo del
   caracter leido */

#include <stdio.h>

main(){
  int c;

  c=(getchar() != EOF);
  printf("c = %i \n",c);
}
