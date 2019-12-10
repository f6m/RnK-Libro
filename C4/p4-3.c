/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 4.3 */

/* Programa que simula una calculadora basica, y al cual se le ha agregado la operacion modulo %*/


#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h> 

#define MAXOP 100
#define NUMBER '0'


int getop(char []);
void push(double);
double pop(void);
int pope(void);
int getch(void);
void ungetch(int);
double atof(char []);

main(){

  int type;
  double op2;
  int ope2;
  char s[MAXOP];

  while((type = getop(s)) != EOF){
	  switch(type){
	  case NUMBER: 
	    push(atof(s));
	    break;
	  case '+':
	    push(pop() + pop());
	    break;
	  case '*':
	    push(pop()*pop());
	    break;
	  case '-':
	    op2 = pop();
	    push(pop() - op2);
	    break;
	  case '/':
	    op2 = pop();
	    if (op2 != 0)
	      push(pop()/op2);
	    else
	      printf("Error: Division por cero en la operacion division\n");
	    break;
	  case '%':
	    ope2 = pope();
	    if (ope2 != 0)
	      push(pope() % ope2);
	    else
	      printf("Error: Division por cero en la operacion modulo\n");
	    break;
	  case '\n':
	    printf("\t %.8g\n",pop());
	    break;
	  default:
	    printf("Error: Comando desconocido %s\n",s);
	    break;
	  }

	}
	return 0;
	}

  #define MAXVAL 100
  int sp = 0;
  double val[MAXVAL];


  /* Funcion push para introducir a la pila */
  void push(double f)
  {
    if (sp < MAXVAL)
      val[sp++] = f;
    else 
      printf("Error: pila llena, no puede efectuar push %g\n",f);
  }

  /* Funcion pop para regresar el valor superior de la pila */
  double pop(void){
    if(sp > 0)
      return val[--sp];
    else{
      printf("Error: pila vacia \n");
      return 0.0;
    }
  }


/* Version de pop que regresa un valor entero */ 
 int pope(void){
    if(sp > 0)
      return val[--sp];
    else{
      printf("Error: pila vacia \n");
      return 0;
    }
  }



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
      ungetch(c);
    return NUMBER;
  }

  #define BUFSIZE 100
  char buf[BUFSIZE];
  int bufp = 0;

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



/* La funcion atof que convierte una cadena a un numero flotante (double)*/
 
double atof(char s[]){
  double val, power;
  int i, sign;

  for(i=0;isspace(s[i]);i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if(s[i] == '+' || s[i] == '-')
    i++;
  for(val = 0.0; isdigit(s[i]);i++)
    val = 10.0*val + (s[i] - '0');
  if(s[i] == '.')
    i++;
  for(power = 1.0;isdigit(s[i]);i++){
    val = 10.0*val + (s[i] - '0');
    power *= 10.0;
  }
  return sign*val/power;
}
