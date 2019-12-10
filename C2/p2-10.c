/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.10 */

/* Programa que lee una cadena de la entrada estandard y si esta contiene mayusculas las covierte a minusculas, esto se lleva a cabo mediante la funcion lower en la cual se utiliza el operador condicional ?:*/

#include <stdio.h>
#include <string.h>


int lower(int );
  char line[' '];

main()
{

  int c,max,i=0,j;

  while((c=getchar()) != EOF && c != '\n'){
    line[i++] = c;
  }
  max = i;

  for(j=0;j <= max; j++){
  line[j]=lower(line[j]);
  }

 if (max > 0) //Hubo una linea
   printf("%s",line);
 return 0;
}

int lower(int c){
  return (c >= 'A' && c <= 'Z')? c + 'a' -'A': c;
}
