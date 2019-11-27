/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.11 */

/* wc - Unix
palabra = cualquier sequencia de caracteres que no contiene blancos ni tabulaciones
¿ Como probaria el programa para contar palabras ? ¿ Que clase de entrada es la mas conveniente para decubrir errores 
si  estos existen ?
R: Pasaria como entrada al programa un archivo de texto, por ejemplo un archivo sin tabs ni blanks, o uno para el cual previamente conozco los resultados. Usando 
 p1-11 < archivo. */

#include <stdio.h>

#define IN 1
#define OUT 0

main() {
int c,nl,nw,nc,state;

state = OUT;
nl = nw = nc = 0;
while((c=getchar()) != EOF) {
	++nc;
	if(c=='\n')
	++nl;
	if(c==' ' || c == '\n' || c == '\t')
		state = OUT;
	else if (state == OUT){
		state = IN;
		++nw;
		}
        }
printf(“%d %d %d \n”,nl,nw,nc);
}


