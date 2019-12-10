/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.7 */

/* Programa que dado un numero entero, en base a su representacion binaria convertimos los n bits que principian apartir de la */
/* posicion p y los invertimos tomando su complemento. */

#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);

main(){

  unsigned x=16;
 
  printf("%i \n %i\n",x, getbits(x,4,3));
}


/* Esta funcion despla./za p unidades toma lo n valores requeridos y hace la operacion */
/* de OR entre x , x recorrido p unidades y el con el complemento del intervalo de bits de x */
  
unsigned getbits( unsigned x, int p, int n)
{
    
  return x | ((x >> (p+1) - n))  | (~((x >> (p+1) - n)) & ~(~0 << n));
}
