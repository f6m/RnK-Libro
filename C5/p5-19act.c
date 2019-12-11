/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.19 */

/* Programa que convierte una descripcion verbal como "x es una funcion que regresa un apuntador a un arreglo de apuntadores a funciones que regresan char" que se expresa como x()*[]*()char y se convertira en char(*(*x())[])()  */

/* Observaciones 
   1: El programa procesa la entrada EN SINTAXIS ABREVIDADA, es decir que 
no procesa "x es un entero" si no "x int" o "x es una funcion" si no
"x()"... 
   2: El ejemplo que propone el libro es:
   "funcion que regresa un apuntador a un arreglo de apuntadores
a funciones regresando un char" que lo traduce en: x()*[]*()*char y 
undcl lo pone como char(*(*(*x())[])()). Otro ejemplo seria 
"Funcion que regresa un apuntador a un int" seria traducida a x()*int
y se volveria int *x() pero undcl lo pone como: int(*x()), aqui 
hay unos parentesis redundantes, es decir que sobran.
 */

/* Tener en cuenta la presedencia: (), {(),[]}, *
   /* 
(1) x es un arreglo de 5 apuntadores a char:
Correcto: char *x[5]
Sintaxis abrevidada: x[5]*char
Salida char (*x[5]) //Redundante
Salida Actual: char *x[5] 

(2) x es un apuntador a un arreglo de 5 char 
Correcto char (* x)[5]
Sintaxis abrevidada x*[] char
Salida: char (*x)[] //Correcto

(3) x es un apuntador a una funcion que regresa un apuntador a int
Correcto: int* (* x)()
Sintaxis abreviada: x*()*int
Salida Corregida:int *(*x)()


(4) x es un arreglo de 5 apuntadores a una funcion que regresa
un apuntador a un arreglo de apuntadores a char.
Correcto: char* (*(*x[5])())[];
Sintaxis abrevidada: x[5]*()*[]*char
Salida:  char *(*(*x[5]))
Salida:   char* (*(*x[4])())[] 

*/
/* Problema: Quitar parentesis redudantes en la entrada.
Consideracion: Si en la sintaxis abreviada encontramos "* nombre" esto no lleva parentesis 

Sintaxis abreviada: x()*int
Salida: int  *x()

Sintaxis abreviada: x()*[]*()*char 
x es una funcion que devuelve un apuntador a un arrglo de apuntadores a una funcion que devuelve un char

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXTOKEN 100

/* int getch(void);
void ungetch(int);
int gettoken(void); */

  #define BUFSIZE 100
  char buf[BUFSIZE];
  int bufp = 0;

  //Regresa buf[] o lee un caracter
  int getch(void)
  {
    return (bufp >0) ? buf[--bufp] : getchar();
  }

  //mete c al bufer
  void ungetch(int c)
  {
    if (bufp >= BUFSIZE)
      printf("ungetch: demasiados caracteres \n");
    else
      buf[bufp++] = c;
  }

enum{NAME, PARENS, BRACKETS}; //0,1,2

char token[MAXTOKEN];
char out[1000];
int tokentype;

int gettoken(void)
{
  int c;
  char *p= token;
  
  while((c=getch()) == ' ' || c == '\t')
    ;
  if(c == '('){
    if((c = getch()) == ')'){
	 strcpy(token,"()");
	 return tokentype = PARENS;
       }
       else{
	 ungetch(c);
	 return tokentype = '(';
       }
       } 
    else if(c == '['){
      for(*p++ = c;(*p++ = getch()) != ']';) //
	;
      *p = '\0';
      return tokentype = BRACKETS;
    }
    else if(isalpha(c)){
      for(*p++ = c;isalnum(c = getch());)
	*p++ = c;
      *p = '\0';
      ungetch(c);
      return tokentype = NAME;
    }
    else return tokentype = c;
}


/* Observacion: usa main como la funcion undcl*/
int main(){
  int type;
  char temp[MAXTOKEN];

    while(gettoken() != EOF){ //name, (), [], o c
      strcpy(out,token); //x 
      while((type = gettoken()) != '\n') //mientras no hay nueva linea
	if(type == PARENS || type == BRACKETS)
	  {
	  strcat(out,token);
          strcat(out," "); /*Agregamos espacio*/
	  }
	else if(type == '*'){
	  if((type = gettoken()) == NAME) //el token siguiente es nombre
	    { 
	      // sprintf(temp," *%s ",out);
	      // strcpy(out, temp); //copia temp al principio de la cadena out

	      sprintf(temp,"%s *%s",token, out);
	    }
	  else {
	    sprintf(temp,"(*%s)",out);
	    if(type == PARENS || type == BRACKETS)
	  {
	  strcat(temp,token);
          strcat(temp," "); /*Agregamos espacio*/
	  }
            //strcpy(out, temp); //copia temp al principio de la cadena out
	    //sprintf(temp,"%s (*%s)",token, out);
	  }
	   strcpy(out, temp); //copia temp al principio de la cadena out
	}
	else if (type == NAME){ //no entra aqui
	  sprintf(temp,"%s %s",token,out);
	  strcpy(out,temp);
	} 
	else printf("entrada invalida en %s\n",token);
      printf("%s\n",out);
    }//while EOF
  return 0;
}


/* Main debe conocer antes las funciones gettoken, dcl y dirdcl*/
/* 
int main(){
  /* int type;
  char temp[MAXTOKEN];/*Cadena de caracteres de tamaño MAXTOKEN */
/*
 while(gettoken() != EOF){ /*EOF = C^d*/
/*    out[0]='\0'; /*Final de la cadena \0 a out*/
/*    undcl(); /* imprime "apuntador a y procesa la cadena con dirdcl */
/*    if(tokentype != '\n') /* Si no hay fin de linea poner error */
/*	{
	error = 1;
	printf("Error 2: De sintaxis, falta enter \n");
	}
      if(error == 0)
      printf("%s: %s %s\n",name,out,datatype); /* Imprime los resultados nombre es la variable, out son las palabras y datatype es el tipo */
/*    error=0; */
      /* name[0]='\0';
      out[0]='\0';
      datatype[0]='\0'; */
/*  }
  return 0;
}*/



	 


	  
	
      
