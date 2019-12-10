/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 4.14 */

/* El siguiente programa muestra el ejemplo de unA MACRO, usando directivas del preprocesador */
/* la macro se llama swapt(t,x,y) */
/* su proposito es cambiar x<->y, ambos x,y de tipo de datos t*/

/* Recordar: '\0' es el caracter llamado nulo de fin del arreglo o cadena cuyo valor es 0,
 * las llamadasa las funciones cuando se pasa un arreglo son por referencia */

#include <stdio.h>
#include <string.h>

#define swapt(t,x,y) t c=y;y=x;x=c;

#undef swaptt
swaptt(int x,int y)
{
  int c;
  
  c=y;
  y=x;
  c=x;
}

main(){
  int a=9,b=6;
  printf("%i %i\n",a,b);
  swapt(int,a, b);
  printf("%i %i\n",a,b);
  swaptt(a,b);
  printf("%i %i\n",a,b);
}

