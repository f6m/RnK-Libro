/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 6.1 */

/* Programa que usa una estructura de datos y cuenta la ocurrencia de las palabras 
reservadas de C, y en donde se ha modificado la funcion getword tomando
en cuenta:

(1)las subrayas _ (revisar la nomenclatura de C para los identificadores)

Ids:
i1) Consta de uno o más caracteres.
    
i2) El primer carácter debe ser una letra o el carácter subrayado (_), mientras que, todos los demás pueden ser letras, dígitos o el carácter subrayado (_). 
Las letras pueden ser minúsculas o mayúsculas del alfabeto inglés. 
Así pues, no está permitido el uso de las letras 'ñ' y 'Ñ'.

i3) No pueden exitir dos identificadores iguales, es decir, dos elementos de un programa no pueden nombrarse de la misma forma. Lo cual no quiere decir que un identificador 
no pueda aparecer más de una vez en un programa.


__FILE__

(2) las cadenas constantes "Como estas". Consideremos esta entrada:
./a.out
"int char int"
   1 char
   1 int

Obs: Un problema aqui contemplar que no haya comillas del cierre.

(3) los cometnarios /* commentarios. Una palabra no cuenta como reservada si esta entre comentarios.
./a.out
/* "hola int" int /*hola char*/ 
/* char
 Salida:   1 char
   1 int */
 

/* (4) Las lineas de control para el preprocesador tales como:
https://www.math.utah.edu/docs/info/cpp_1.html

./a.out
_int %float %char
   1 char
   1 float

Se cambio a:
./a.out
_int %char %char int char
   1 char
   1 int


#include
#define */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

/* Estructura para la pareja (palabra, numero de ocurrencias) */
struct key {
char *word;
int count;
} keytab[] = {
  "auto",0,
  "break",0,
  "case",0,
  "char",0,
  "const",0,
  "continue",0,
  "default",0,
  "do",0,
  "double",0,
  "else",0,
  "enum",0,
  "extern",0,
  "float",0,
  "for",0,
  "goto",0,
  "if",0,
  "int",0,
  "long",0,
  "register",0,
  "return",0,
  "short",0,
  "signed",0,
  "sizeof",0,
  "static",0,
  "struct",0,
  "switch",0,
  "typedef",0,
  "union",0,
  "unsigned",0,
  "void",0,
  "volatile",0,
  "while",0,
};

/* Definicion de las funciones */
int getword(char *, int);
int getch(void);
void ungetch(int);
int binsearch(char *,struct key *, int);

/* Conteo de frecuencia de palabras reservadas */
main(int argc, char *argv[]){

int n, nkeys;

/* Como el tamaño del arreglo keytab es calculado por el compilador */
/* Le indicamos cuatas entradas tiene calculandolas */
nkeys = sizeof(keytab) / sizeof(keytab[0]);

/* Array para guardar una palabra */
char word[MAXWORD];

while ((getword(word, MAXWORD) != EOF)) //EOF = ctrl+d
	if(isalpha(word[0])) //Si empieza con una letra...
		if((n = binsearch(word,keytab, nkeys)) >= 0) //si se encuentra word en keytab con tamaño nkeys
			keytab[n].count++;
 for(n=0;n< nkeys;n++)
	if(keytab[n].count > 0)
		printf("%4d %s\n", keytab[n].count,keytab[n].word);
  return 0;
}

/* Funciones que manejan el buffer */

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

    
/* La funcion que obtiene las palabras */

int getword(char *word, int lim)
{
  int c,e;
  char *w = word;

    while(isspace(c = getch()) || c=='\t') /* ignora los espacios en blanco y tabs */
      ;
    if(c != EOF)
	*w++ = c;
    //if(!isalpha(c)){ //Si es la primer letra un Aa Bb..Zz
    // *w = '\0'; //Si no lo es agregamos \0 find e cadena
    // return c; //regresamos 
    //}
    if(c=='"')
      while((c=getch()) != '"') //avanza si es cadena constante, asumiento que no es solo un caracet "
	{if(c==EOF){printf("Error: faltan comillas derechas\n"); return c;}}
    if(c=='/' && (c=getch()) == '*')
	while((c=getch()) != '*' && (e=getch()) != '/')
	{if(c==EOF){printf("Error: faltan simbolos */ derechos\n"); return c;}}								 
    if(isalpha(c) || c=='_' || c=='"' || c=='/' || c=='%'){
    for(;--lim > 0;w++) //mientras lim aun sea positivo, incrementa el apuntador de word
      if(!isalnum(*w = getch())){ //es Aa...Zz | 0,..,9
	ungetch(*w); //si no lo es lo metems a buffer
	break; //rompes el ciclo for
      }
    } else { //
	 *w = '\0'; //Si no lo es agregamos \0 find e cadena
	 return c; //regresamos 
      }
    *w ='\0'; //fin de cadena
    return word[0]; //regresamos el apuntador a word su primera letra
}

 	 
/* Funcion que realiza la busqueda de la palabra */

int binsearch(char *word, struct key tab[], int n){
int cond;
int low, high, mid;

low = 0;
high = n - 1;

 while ( low <= high ){ //usamos menor o igual 
   mid = (low + high) / 2;
	if((cond = strcmp(word, tab[mid].word)) < 0)
	high = mid - 1;
	else if (cond > 0)
		low = mid + 1;
	else return mid;
}
return -1;
}
  
