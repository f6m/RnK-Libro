/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.18 */

/* Programa que borra los tabuladores y blancos al final de cada linea de entrada y tambien las lineas en blanco */

#include <stdio.h>
#include <stdlib.h>

/* Falta que al correrlo bajo un archivo salga correctamente */
/* Estas funciones afectan los arreglos line, to, from*/

int getlinelength(char line[]);
void copy(char to[], char from[]);

// Imprime la line de entrada mas larga aceptando cualquier logintud de cadenas

main()
{
int len, max;

char line[' '];
char without[' '];

/* Quita los blancos y los tabuladores, luego tambien las lineas en blanco de las lineas de entrada */

 while((len = getlinelength(line)) >= 0){
   for(max=len-1;line[max]==' ' || line[max]=='\t';max--){}
   line[max+1]='\0';
   copy(without,line);
   if (len > 0) //Hubo una linea
     printf("%s\n",without);
 }
 exit(1);
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


