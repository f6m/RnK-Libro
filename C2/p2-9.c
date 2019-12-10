/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.9 */

/* Programa que implementa una funcion bitcount(x) que cuenta * /
/* los bits de un etero unsigedn usando complemento a dos*/

/* x &= (x-1)
 * x - 1 pone a 0 el bit mas a la derecha de x: x=11,x-1=10, pueso que restar uno
 tiene como efecto en
  binario quitar el bit mas a la derecha t*/
/* x & (x - 1) : x - 1 */

#include <stdio.h>

int bitcount(unsigned y);
int bitcount2(unsigned y);

main(){

  unsigned int x=7;
  printf("El numeo %i \t tiene %i bits 1\n",x,bitcount2(x));
  x = x & (x - 1);
  printf("Nuevo numero %i\n",x);
  
}

int bitcount(unsigned y)
{
  int b;
  for(b=0; y!=0; y >>= 1)
  {
   if(y & 01) /* Si aun hay bit */
        b++;
  }
   
   return b;
}

int bitcount2(unsigned y)
{
  int b=0;
  for(b=0;y!=0;(y&=(y-1)))
  {
    b++;
  }
   
   return b;
}
