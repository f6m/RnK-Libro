/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.22 */

/* El siguiente programa divide las lineas de caracteres mas largas de un programa en dos lineas mas cortas */
/* Consideramos una linea grande lineas de mas de 10 caracteres */

#include <stdio.h>

int getline(char line[]);
void copy(char to[], char from[]);
void copyandiv(char to[], char from[]);



// Imprime la line de entrada mas larga aceptando cualquier logintud de cadenas

main()
{
  int len, max, i;

 char line[1000];
 char longest[1000];


 max=0;
 while((len = getline(line)) > 0){
   printf("La linea es %s\n",line);
 if (len > 20) //Hubo una linea con mas de 20 caracteres
   {
     printf("Sera dividida en 2\n");
     // Inserta el caracter de division en un espacio. para no interferir con las silabas de la palabra
     copyandiv(longest,line);
     printf("La linea dividida es [%s] con longitud %i \n",longest,strlen(longest));
   }
   }
 printf("%s\n",longest);
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

// copya y divide

void copyandiv(char to[], char from[])
{
  int i;
  char tmp[1000];

  i=0;
  while((*(tmp + i) = from[i]) != '\0')
	++i;
  i=strlen(from)/2;
  tmp[i] = '\n';
  while((*(tmp+(i+1)) = from[i]) != '\0')
	++i;
  i=0;
  while((*(to+i) = tmp[i]) != '\0')
	++i;
}




