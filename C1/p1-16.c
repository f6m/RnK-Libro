/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.16 */

/* Programa que nos muestra la linea mas larga de la entrada estandar sin importar cuan larga es la linea */

#include <stdio.h>

int getline(char line[]);
void copy(char to[], char from[]);


// Imprime la line de entrada mas larga aceptando cualquier logintud de cadenas

main()
{
int len, max;

char line[' '];
char longest[' '];


 max=0;
 while((len = getline(line)) > 0)
   if(len > max){
     max = len;
     copy(longest, line);
   }
 if (max > 0) //Hubo una linea
   printf("%s",longest);
 return 0;
}


// getline: Regresa la longitud de line

int getline(char s[])
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


