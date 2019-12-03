/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.23 */

/* El siguiente programa elimina los comentarios de un programa en C */
/* suponemos que el programa esta bien escrito y que los comentarios estan bien cerrados */
/* ctl + d es EOF */

#include <stdio.h>

#define MAX 10000
void erasecomments(char s[], int leng);


main()
{
 int len, i;
 char line[MAX];
 char c;

 
 i=0;
 while((c = getchar()) != EOF){
    line[i++]=c;
 }
 printf("El texto es: %s\n",line);
 printf("Longitud:%i\n",i);
 erasecomments(line,i);
 printf("El texto sin comentarios es: %s\n",line);
// printf("Nva. longitud:

 return 0;
}

// borra lo que encuentra entre comentarios 
void erasecomments(char s[],int leng)
{
 int i,j,r,t;

 for(i=0;i<=leng;i++)
  {
  if (s[i] == '/' && s[i+1]=='*'){
     printf("Indice inicial: %i\n",i);
     j=i+2; /*primer caracter dentro del comentario */   
     while(s[j] != '*' && s[j+1] != '/') 
         {
            ++j;
      }
     printf("Indice final: %i\n",j+2);
     t=i;
     r=j+2;
     while(r<=leng){
	s[t]=s[r];
	r++;t++;
	}
   }

 }
}





