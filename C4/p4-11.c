/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 4.11 */


/* Programa que simula una calculadora basica, modificamos la funcion getop para que no necesite la funcion ungetch */
/* agregamos una variable static interna en getop */
/* este archivo se llama getop.c se compila por separado para ver su uso junto al resto del programa */

/* En este archivo incluimo la funcion mas grande getop() */
#include <stdio.h> /*para usar getch() */
#include <ctype.h> /* para usar isdigit() */
#include "calc.h" /* para usar getch()/ungetch() */

/* #define BUFSIZE 100 */
  static char buf[100];
  static int bufp = 0;

  /* Funcion getop para obtener el siguiente operador u oparando numerico */
  int getop(char s[])
  {
    int i,c;

    while((s[0] = c = getch()) == ' ' || c == '\t')
      ;
    s[1]='\0';
    if (!isdigit(c) && c != '.')
      return c;
    i = 0;
    if (isdigit(c))
      while(isdigit(s[++i] = c = getch()))
	;
    if (c == '.')
      while(isdigit(s[++i] = c = getch()))
	;
    s[i] = '\0';
    if (c != EOF)
      buf[bufp++] = c;
    return NUMBER;
  }

  
  int getch(void)
  {
    return (bufp >0) ? buf[--bufp] : getchar();
  }

  void ungetch(int c)
  {
    if (bufp >= BUFSIZE)
      printf("ungetch: demasiados caracteres \n");
    else
      buf[bufp++] = c;
  }

