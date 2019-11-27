/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.12 */

/* Programa que lee la entrada estandar del teclado y cada palabra por una linea en la salida*/

#include <stdio.h>

main(){
  int c,k;


  while((c = getchar()) != EOF)
    {
      switch(c){
      case ' ':putchar('\n');break;
      case '\t':putchar('\n');
      }
      if(!(c == '\t' || c==' ' || c==' '))
      putchar(c);
	 }    
}
