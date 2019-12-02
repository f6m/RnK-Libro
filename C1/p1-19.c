/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.19 */

/* Programa que dada una cadena de cualquier longitud en la entrada estandard imprime dicha cadena invertida */

#include <stdio.h>
#include <string.h>


void reverse();
  char line[' '];

main()
{

  int c,max,i=0;

  while((c=getchar()) != EOF && c != '\n'){
    line[i++] = c;
  }
  max = i;

  reverse();

 if (max > 0) //Hubo una linea
   printf("%s",line);
 return 0;
}

void reverse(void)
{
  int i,j,k;
  extern char line[' '];

    for(i=0,j = strlen(line)-1;i<j;i++,j--){
      k = line[i];
      line[i] = line[j];
      line[j] = k;
    }
}
