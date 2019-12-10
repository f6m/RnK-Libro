/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 4.9 */

/* Las modificaciones las adaptamos en getch1, ungetch1 */
/* Las funciones getch , ungetch no manejan correctamente un EOF que se regresa, es decir un EOF que se paso de mas en la entrada final */
/* Decida cuales deben ser sus propiedades si se regresa un EOF, y despues realice su diseño */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h> 

#define MAXOP 100
#define NUMBER '0'
#define SIN '1'
#define COS '2'
#define EXP '3'


int getop(char []);
void push(double);
double pop(void);
int pope(void);
int getch(void);
void ungetch(int);
/* double atof(char []); */

/* variables globales */
#define MAXVAL 100
  int sp = 0;
  double val[MAXVAL];

int getch1(void);
void ungetch1(int);

main()
{
  int c;
  
  c = getch1();
  printf("c = %i \n",c);
  ungetch1(c);
  c = getch1();
  printf("c = %i \n",c);
  printf("EOF = %i\n",EOF);

  int type;
  double op2;
  int ope2;
  char s[MAXOP];

  while((type = getop(s)) != EOF){ /* El tipo getop es regresado como int */
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
	  case SIN: push(sin(pope()));break;
	  case COS: push(cos(pope()));break;
	  case EXP: push(exp(pope()));break;
	  case '\n': /* cada vez que tecleamos saca el valor den la pila */
	    printf("\t %.8g\n",pop()); /* imprime el ultimo valor de la pila */
	    break;
	  default:
	    printf("Error: Comando desconocido %s\n",s);
	    break;
	  } /* end switch */

	} /* end while */
	return 0;
	} /* end main */

  
  /* Funcion push para introducir a la pila */
  void push(double f)
  {
    if (sp < MAXVAL) /* sp < 100? */
      val[sp++] = f; /* la primera vez entra con val[0] */
    else 
      printf("Error: pila llena, no puede efectuar push %g\n",f);
  }

  /* Funcion pop para regresar el valor superior de la pila */
  double pop(void){
    if(sp > 0)
      return val[--sp]; /* para llamar a pop almenos debe haber un valor la primer llamada lo hace a val[0] */
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
  int getop(char s[]) /* recive un arreglo de caracteres como entrada */
  {
    int i,c;

    /* El analisis se realiza caracter por caracter con la funcion getchar() de string.h */
    while((s[0] = c = getch1()) == ' ' || c == '\t')  /* mientras no nay nada en buffer buf leer caracter, si es espacio blanco o tabulador ignorar */
      ;  /* pone el caracter leido en s[0] si son muchos blancos o tabuladores todos los pone s[0] */
    s[1]='\0'; /* pone el fin de la cadena en s[1] */
    i=0;
    if(isalpha(tolower(c))){
      s[0]=c;
      while((isalpha(s[++i] = c = getch1())) && i<3)
      ;
     s[3]='\0';
     printf("expresion %s \n",s);
     if (s[0]=='s' && s[1] == 'i' && s[2] == 'n'){
       printf("SIN %s\n",s);
       return SIN;
     }
     
     if (s[0]=='c' && s[1] == 'o' && s[2] == 's'){
       printf("COS %s\n",s);
       return COS;
     }
     if (s[0]=='e' && s[1] == 'x' && s[2] == 'p'){
       printf("EXP %s\n",s);
       return EXP;
     } 
    }
     
    if (!isdigit(c) && c != '.') /* si no fue blanco o tabulador revisa si no es un digito y si no es un punto decimal regresa el simbolo, esto para asegurarnos que no fue numero real */
      return c; /* pudimos haber tecleado "#$ o otros simbolos y regresa el control */
    i = 0; /*volvemos el indice para la cadena a 0 */
    if (isdigit(c)) /* si es digito el primer caracter */
      while(isdigit(s[++i] = c = getch1())) /* lo almacenamos en s[0] y a continuación leemos el siguiente caracter o caracteres mientras sea digito y los almacenamos, esto porque aun no llegamos a ungetch*/
	;
    if (c == '.') /* cuando encontremos el punto decimal es señal que vienen mas digitos*/
      while(isdigit(s[++i] = c = getch1())) /*continuamos leyendo digito por digito y almacenandolo en s */
	;
    s[i] = '\0'; /*poemos el final de la cadena */
    if (c != EOF) /* Si no hemos introducido ctl + D pone el ultimo caracter leido en el buffer*/
      ungetch1(c);
    return NUMBER;
  }

  #define BUFSIZE 100
  char buf[BUFSIZE]; /* arreglo de caracteres */
  int bufp = 0; /* su indice */

  int getch(void)
  {
    return (bufp > 0) ? buf[--bufp] : getchar(); /* regresa buf[--bufp] si bufp > 0 o getchar() funcion que obtiene un caracter de la entrada estandar */
  }

  void ungetch(int c) /*pone el caracter en el buffer */
  {
    if (bufp >= BUFSIZE)
      printf("ungetch: demasiados caracteres \n");
    else
      buf[bufp++] = c;
  }



/* La funcion atof que convierte una cadena a un numero flotante (double)*/
 
/* double atof(char s[]){
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
} */ 

/* Modificacion a getch */
  int getch1(void)
  {
    // return (bufp >0) ? buf[--bufp] : getchar();
   int c;
   if(bufp>0) /* Si hay algo en buf ]*/
      return buf[--bufp]; /* regresar contenido */
   else
      return c=getchar(); /* regresamos el caracter o el simbolo leido sin importar si es -1 = EOF */ 
  }

  /* Modificación a ungetch */
  void ungetch1(int c)
  {
    if (bufp >= BUFSIZE)
      printf("ungetch: demasiados caracteres \n");
    else
      buf[bufp++] = c;
  }


