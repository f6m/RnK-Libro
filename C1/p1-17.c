/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.17 */

/* Programa que nos muestra las linea de la entrada estandar cuando la linea de entrada tiene mas de 80 caracteres */

#include <stdio.h>

int getlinelength(char line[]);
void copy(char to[], char from[]);


// Imprime la line de entrada mas larga aceptando cualquier logintud de cadenas

main()
{
  int len, max;

char line[' '];
char longest[' '];

 max=0;
 while((len = getlinelength(line)) >= 0){
 
   /* getline afecto a line ahora line tiene la linea de entrada */
   
   if(len >= 5)
     printf("linea %s\n",line);
   
 }
 return 0;
}


// getline: Regresa la longitud de line

int getlinelength(char s[])
{
  int c,i=0;

  while((c=getchar()) != EOF && c != '\n'){
    s[i++] = c;
  if (c == '\n'){
    s[i++] = c;
  }
   }

  s[i]= '\0';
  return i;
}

// copy: copia 'from' en 'to'; supone que to es suficientemente grande

void copy(char to[], char from[])
{
  int i;

  i=0;
  while((to[i] = from[i]) != '\0')
	++i;
	}


