/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 4.13 */

/* El siguiente programa muestra el ejemplo de la funcion reverse recursiva */
/* que invierte una cadena de caracteres */

/* Recordar: '\0' es el caracter llamado nulo de fin del arreglo o cadena cuyo valor es 0,
 * las llamadasa las funciones cuando se pasa un arreglo son por referencia */

#include <stdio.h>
#include <string.h>

void printd(int);
void reverse(char []);
void reverrever(char [],int, int);

main(){
  char cadena[]="1231";

  printd(122);
  
    reverse(cadena);

  printf("Funcion reverse() Normal, Cadena %s \n",cadena); 
      reverrever(cadena,0,strlen(cadena));

  printf("Funcion esrever() (reverse recursiva), Cadena %s\n",cadena); 
  
}

void printd(int n)
{
  if (n < 0)
    {
      putchar('-');
      n= -n;
    }
  if (n/10) /* si es mayor que cero n/2 */
    printd(n/10); /* solo hasta el ultima llamada de printd cuando la condicion n/10 es menor que 0 pasa a imprimir
    el primer digito del numero, las demas llamadas a printd como no terminaron se almacenaron en una pila los valores de llamada
    y no se llego al puchar(), esto se recupera para cada una volviendo al putchar en orden ascendente */
  putchar(n % 10 + '0');
}

void reverrever(char s[], int l, int r) {
    int c, i=l, j = r-1;
    
    if(l==r)
      return;
    
    c = s[i];
    s[i] = s[j];
        s[j] = c;
	
    reverrever(s,l+1,r-1);
}


void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
