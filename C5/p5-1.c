/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.1 */

/* Programa que adapta el uso de las funcion getint para convertirla en getfloat, y 
 * leer un double, si no es un double regesar 0, cuando termine regresar EOF,
 * almacenar el double en un apuntador */
/* Numero de programa (El lenguaje de programacion C, R&K, segunda edicion): 5.2 */
/* EOF = -1 se devuelve cuando oprimes intro */ 

#include <ctype.h>
#include <stdio.h>


int getch(void);
void ungetch(int);
int getint(double *);


main(){
  #define SIZE 5
  
  int n, i;
  double array[SIZE];
  
  /* llena array con los numeros introducidos */
  for( n = 0;n < SIZE && getint(&array[n]) != EOF;n++)
	 ;
  for(i=0;i<SIZE;i++)
    printf("Array[%i] = %f\n",i,array[i]);
}


int getint(double *pn)
{
  int c, sign;
  while (isspace(c = getch())) /* ignoramos lo espacios en blanco */
    ; /* en el momento de dejar de teclear algo que no es espacio se sale de este ciclo */ 
  if (!isdigit(c) && c != EOF && c!= '+' && c!='-'){ /* Si no es digito, no es caracter + o - --> no es numero */
    ungetch(c); /* meterlo al buffer si es que cabe e incremente al apuntador del buffer*/
    return 0; /* terminar  y regresar 0 */
  }
  sign = (c == '-') ? -1:1; /*si es signo negativo, asignar -1 la var. sign si es cualquier otra cosa asignar 1*/
  if (c == '+' || c == '-') /* si c es + o es - */
  {  
    *pn = c; /* asignamos el valor entero del caracter + o - a *pn */
    c = getch(); /* regresa lo del buffer o lee un caracter */
  }
  /* ponemos esta condicion de verificacion si es digito c para evitar que entre al inicializar *pn=0 en el for*/
  if(isdigit(c)) /* leiste el primer digito, entonces sigue leyendo, no hay nada el buffer */
  {
  for(*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0'); /* c-'0' devuelve el digito decimal del caracter c, lee otro y los va conviertiendo a su numero decimal */
  }
  *pn *= sign;
  if (c != EOF)
    ungetch(c); /*metes el valor del caracter intro al buffer */
  return c;
}


  #define BUFSIZE 100
  char buf[BUFSIZE];
  int bufp = 0;
   
/* pregunta si el indice es mayor a 0, en cuyo caso se utilizo ya el arreglo y devuelve buf[--buf]
   si no devuelve la lectura de un caracter*/
  int getch(void)
  {
     return (bufp > 0) ? buf[--bufp] : getchar();
  }

/* si bufp que es una variable global es mayor que el indice permitido, entonces ya no puedo meter
   nada y lo informamos, si no mete c al buffer e incrementa el indice bufp */
  void ungetch(int c)
  {
    //if (c == EOF) exit(0);
    if (bufp >= BUFSIZE)
      printf("ungetch: demasiados caracteres \n");
    else
      buf[bufp++] = c;
  }
