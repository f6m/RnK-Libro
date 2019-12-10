/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.2 */

/* Escribir un enunciado equivalente al siguiente ciclo
for(i=0;i < lim - 1 && (c=getchar()) != '\n' && c != EOF; ++i)
s[i]=c;
Utilizamos Ctrl + D para indicar el EOF
compilamos con cc -o p p1-20.c -lm
*/

#include <stdio.h>
#include <string.h>
#define lim 10
char s[lim];

main(){
  int i;
  char c;

   for(i=0;i <= lim - 1 && (c=getchar()) != '\n' && c != EOF; ++i)
   { 
     s[i]=c;
     printf("Caracter guardado:%c El valor de i es %d\n",c,i);
   }
  
   //s[i++]='\0';
   printf("Cadena guardada por el for:%s con longitud:%d\n",s,strlen(s));
   i=0;
   while(lim - 1 >= i)
   {
     if((c = getchar()) != '\n')
     {
       if(c!=EOF)
       {
	 s[i]=c;
	 printf("Caracter guardado:%c El valor de i es %d\n",c,i);
	  ++i;
       }
     }
   }
	  
    printf("Cadena guardada por los whiles:%s\n",s);
          
}
 
 
