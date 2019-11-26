/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.9 */

/* Programa que lee la entrada estandar del teclado y cuando hay mas de dos blancos
los convierte en uno solo y muestra esa salida*/

#include <stdio.h>

main(){
  int c,k;


  while((c = getchar()) != EOF)
    {
      if(!(k == ' ' && c == ' '))
	putchar(c);
      
	k = c; 
    }    
}
