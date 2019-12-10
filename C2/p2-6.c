/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.6 */

/* Programa que dado un numero entero binario x regresa a x con los n bits que principian en la posicion p iguales
a los n bits mas a la derecha de y, dejando los otros bits sin cambio */


#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);
unsigned int getbits(unsigned int x, int p, int n);

main(){

  unsigned int x=25;
  unsigned int y=7;
 
  printf("%d \n %d\n %d",x,y,setbits(x,4,3,y));
}

unsigned int getbits( unsigned int x, int p, int n)
{
   return (x >> (p+1-n)) & ~(~0 << n);
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
  unsigned int m,t;
  m= (~(~0 << n) & y);
  printf("Apagamos los bits a la izq de y y tenemos %d\n",m);
  t = (~(~0 << p+1-n) & x);
  printf("Apagamos los bits a la izq de x y tenemos %d\n",t);
  return ((m << p+1-n) | t);
  
}
