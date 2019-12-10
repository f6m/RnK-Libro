/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 3.6 */

/* Escribir la funcion itob(n,s,b) que convierte al entero n en una 
representacion de caracteres con base b dentro de la cadena s. En particular
itob(n,s,16) da formato a n como un entero hexadecimal */

#include <string.h>
#include <stdio.h>
 
void itoa1(int n, char s[], int b);
void itoa2(int n, char s[]);
void reverse(char s[]);

main(void) {
    int n = 9;
    int b = 8;
    char s[10]="hola";

    printf("Entero :%i\n",n);
    printf("Cadena :%s\n",s);
    reverse(s);
    printf("Cadena invertida:%s\n",s);
    itoa1(n,s,b);
    reverse(s);	
    printf("Entero Cadena:%s\n",s);  
    return 0;


}

void itoa1(int n, char s[], int b){
  int i,j,sign;
  
  if((sign = n) < 0) /* entero negativo */
    n = -n;
  i=0;
  do{
    s[i++]=n%b + '0';
  }while((n/=b)>0);
  if(sign < 0)
    s[i++]='-';
    s[i]='\0';
   /* reverse(s);*/
}

void reverse(char s[]){
int c,i,j;
for(i=0,j=strlen(s)-1;i<j;i++,j--){
c=s[i];
s[i]=s[j];
s[j]=c;
}
}
