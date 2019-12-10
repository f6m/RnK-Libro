/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.2 */

/* Programa que adapta el uso de las funcion getint para convertirla en getfloat, y 
 * leer un double, si no es un double regesar 0, cuando termine regresar EOF,
 * almacenar el double en un apuntador */

#include <ctype.h>
#include <stdio.h>


int getch(void);
void ungetch(int);
int getfloat(double *);


main(){
  #define SIZE 5
  
  int n, i;
  double array[SIZE];
  
  for( n = 0;n < SIZE && getfloat(&array[n]) != EOF;n++)
	 ;
  for(i=0;i<SIZE;i++)
    printf("Array[%i] = %f\n",i,array[i]);
}


int getfloat(double *pn)
{
  int c, sign, pot;
  double pni=0.0,pnf=0.0;
  
  while (isspace(c = getch())) /* ignoramos lo espacios en blanco */
    ; /* en el momento de dejar de teclear algo que no es espacio se sale de este ciclo */ 
  if (!isdigit(c) && c != EOF && c!= '+' && c!='-'){ /* Si no es digito, no es caracter + o - --> no es numero */
    ungetch(c); /* meterlo al buffer si es primera vez*/
    return 0; /* terminar  y regresar 0 */
  }
  sign = (c == '-') ? -1:1; /*si es signo negativo, asignar -1 la var. sign si es cualquier otra cosa asignar 1*/
  if (c == '+' || c == '-') /* si c es + o es - */
  {  
    pni = c; /* asignamos el valor entero del caracter + o - a *pn */
    c = getch(); /* regresa lo del buffer o lee un caracter */
  }
  /* ponemos esta condicion de verificacion si es digito c para evitar que entre al inicializar *pn=0 en el for*/
  if(isdigit(c))
  {
    /* parte entera del  numero leido*/
  for(pni = 0.0; isdigit(c); c = getch())  
    pni = 10 * pni + (c - '0');
   /* 13 = 1*10^1 + 3*10^0 */
  }
  
  if(c == '.')
  {
    /* pnf = c;asignamos el valor entero del caracter . *pni */
    c = getch(); /* regresa lo del buffer o lee un caracter */
  }
  
  if(isdigit(c))
  {
    pot = 1;
  for(pnf = 0.0; isdigit(c); c = getch())
    pnf =  pnf * (1/10) + (c - '0');
    pot = pot * 10;
    /* 0.34 = 3*(1/10)^1 + 4*(1/10)^2  */
  }
  
  *pn = pni + pnf/pot;
  *pn *= sign;
  
  if (c != EOF)
    ungetch(c);
  return c;
}


  #define BUFSIZE 100
  char buf[BUFSIZE];
  int bufp = 0;
   

  int getch(void)
  {
     return (bufp > 0) ? buf[--bufp] : getchar();
  }

  void ungetch(int c)
  {
    //if (c == EOF) exit(0);
    if (bufp >= BUFSIZE)
      printf("ungetch: demasiados caracteres \n");
    else
      buf[bufp++] = c;
  }
