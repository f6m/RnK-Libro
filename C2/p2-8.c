/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.8 */

/* Programa que implementa una funcion rightrot(x,n,p) que apardado un numero entero binario regresa a x rotado
 a la derecha n bits (esto tomando en cuenta que los enteros a manejar tienen un byte de longitud) */

#include <stdio.h>

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);
unsigned int getbits(unsigned int x, int p, int n);
unsigned int rightrot(unsigned int x, int n);

main(){

  unsigned int x=13;
  
  printf("%d \n %d\n",x,rightrot(x,2));
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

unsigned int rightrot(unsigned int x, int n)
{
  //return (x>>n);
  return ((x<<8-n) & ~(~0 << 8)) | (x>>n);
}
