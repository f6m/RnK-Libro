/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.4 */

/* Programa que borra todas las ocurrencias de la cadena s2 previamente definida 
 * en la cadena s1 y nos muestra la cadena resultante */

#include <stdio.h>
#include <string.h>


void squeeze(void);
  char s1[' '];
  char s2[ ]="hola";

main()
{

  int c,max1,max2,i=0,j=0;

  while((c=getchar()) != EOF && c != '\n'){
    s1[i++] = c;
  }
  max1 = i;

  /* while((c=getchar()) != EOF && c != '\n'){
    s2[j++] = c;
  }
  max2 = j;*/
  squeeze();

 if (max1 > 0) //Hubo una linea
   printf("%s",s1);
 return 0;
}

void squeeze(){

  int i,j,k;

  extern char s1[' '];
  extern char s2[ ];

  for(k=0; s2[k] != '\0'; k++){
    for(i=j=0;s1[i] != '\0'; i++){
      if(s1[i]!=s2[k])
	s1[j++]=s1[i];
      s1[j]='\0';
    }
  }
}
