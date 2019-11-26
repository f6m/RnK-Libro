/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.10 */

/* Programa que lee la entrada estandar del teclado y cambia los blancos por B las
tabulaciones por \t los retrocesos por \b y cada diagonal invertida \ por \\ y muestra
la salida*/

#include <stdio.h>

main(){
  int c,k;


  while((c = getchar()) != EOF)
    {
      switch(c){
      case '\t':putchar('\\');putchar('t');break;
      case '\b':putchar('\\');putchar('b');break;
      case '\\':putchar('\\');putchar('\\');break;
      case ' ':putchar('B');break;
      case '\n':putchar('\\');putchar('n');break;
      }
      if(!(c == '\t' || c==' ' || c=='\b' || c == '\\'))
      putchar(c);
	 }    
}
