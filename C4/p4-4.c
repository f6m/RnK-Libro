/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 4.4 */


/* Programa que simula una calculadora basica, y al cual se le ha agregado 
 1.- ordenes para imprimir 
 el elemento al tope de la pila sin sacarlo de la pila
 2.- para duplicar el elmento al tope de la pila
 3.- para intercambiar los dos elementos del tope 
 4.- y una orden para limpiar la pila */


#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h> 

#define MAXOP 100
#define NUMBER '0'


int getop(char []);
void push(double); /* introducir un elemento a la pila */
double pop(void); /* sacar un elemento de la pila */
void dup(int); /* duplicar un elemento de la pila en base a algun valor del indice */ 
void intertop(void); /* intercambiar los dos elementos tope de la pila */ 
int pope(void); 
double print(void); /* Imprimir el elemento tope de la pila */
void clear(void); /*limpiar toda la pila */
int getch(void);
void ungetch(int);
double atof(char []);

main(){

  int type;
  double op2;
  int ope2;
  char s[MAXOP]; /* Cadena temporal que almacena la entrada dentro de getop */

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
  int sp = 0; /* indice de la pila */
  double val[MAXVAL];  /* pila : val[0],...,val[MAXVAL] */


  /* Funcion push para introducir a la pila */
  void push(double f)
  {
    if (sp < MAXVAL) /* Si el indice es menor al tamaño maximo de elementos permitidos para la pila agregar valor a la pila e incrementar el indice */
      val[sp++] = f; /*guardamos el valor en la pila cada vez que invocamos a la funcion push */
    else 
      printf("Error: pila llena, no puede efectuar push %g\n",f); /* si la pila esta llena no se puede guardar nada */
  }

  /* Funcion pop para regresar el valor superior de la pila */
  double pop(void){
    if(sp > 0) /* Podemos sacar siempre y cuando hay algo en la pila */
      return val[--sp]; /* La pila es de valores double asi que al sacar debemos regresar un double */
    else{ 
      printf("Error: pila vacia \n"); /* Si no hay nada --> pila vacia */
      return 0.0; /* y regresamos 0.0 */
    }
  }


/* Version de pop que regresa un valor entero de la pila, no usa operador cast */ 
 int pope(void){
    if(sp > 0)
      return val[--sp];
    else{
      printf("Error: pila vacia \n");
      return 0;
    }
  }

  /* Funcion de pila simulada por el arreglo val e indice sp que imprime el valor actual de la pila */
  double print(void){
    if(sp > 0) /* si hay algo que imprimir imprime */
      return val[sp]; /* no incrementar el indice solo utilizarlo */
    else{
      printf("Error: pila vacia, nada que imprimir \n");
      return 0.0; /* si la pila esta vacia, regresar 0.0 */
    }
  }
  /* duplicar un elemento de la pila en base a algun valor del indice */
void dup(int k){  
 if(sp > 0) /* hay algo que duplicar */
   val[++sṕ]=val[k];
 else
     printf("Error: pila vacia, nada que dupliar \n");
    
}
void intertop(void){ /* intercambiar los dos elementos tope de la pila */
int tmp, idx; /*variables temporales */
 if(sp > 1) /* hay almenos dos indices/elementos para intercambiar */
 {
   idx=sp-1; /*guardamos el indice del penultimo elemento de la pila*/
   tmp=val[idx]; /* el penultimo elemento lo guardamos temporalmente */
   val[idx]=val[sp]; /* copiamos el tope al penultimo elemento */
   val[sp]=tmp; /*copiamos el penulrimo elemento de la pila al tope*/
 }
 else
     printf("Error: No hay almenos dos valores para intercambiar \n");
}

void clear(void){ /*limpiar toda la pila */
sp = 0; /* limpiamos la pila asignando su indice al tope primer elemento */  
val[0]='\0'; /*colocamos el caracter de fin de cadena en la primera posicion */
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
