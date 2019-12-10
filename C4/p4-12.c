/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 4.11 */

/* El siguiente programa muestra el ejemplo de la funcion itoaRecursivo la cual comvierte un numero entero a una cadena de caracteres de manera recursiva */
#include <stdio.h>
#include <string.h>

void printd(int );
void itoa(int, char []);
void itoaRecursivo(int,int);
void reverse(char []);

main(){
  char cadena[' '];
  int x=1231;

  printd(1213);
  itoa(x,cadena);
  printf("Itoa Normal: Entero %i, Cadena %s \n",x,cadena); 
  x = 1234;
  printf("Itoa Recursivo: Entero %i, Cadena \n",x); 
  itoaRecursivo(x,0); 
  
}

void printd(int n)
{
  if (n < 0)
    {
      putchar('-');
      n= -n;
    }
  if (n/10)
    printd(n/10);
  putchar(n % 10 + '0');
}

void itoa(int n, char s[]) {
    int i, sign;
        
    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do {
        s[i++] = n % 10 + '0';
        printf("%d %% %d + '0' = %d\n", n, 10, s[i-1]);
	} while ((n /= 10) > 0);

    /*if(n/10){
    s[i++]= n % 10 + '0';
    itoa(n/10,s);
    }*/

    if (sign < 0)
        s[i++] = '-';
     
    s[i] = '\0';
    reverse(s);
}

void itoaRecursivo(int n,int i) {
  int sign;
  char s[' '];
    
    if ((sign = n) < 0)
        n = -n;
        /* do {
        s[i++] = n % 10 + '0';
        printf("%d %% %d + '0' = %d\n", n, 10, s[i-1]);
	} while ((n /= 10) > 0);*/

    if (sign < 0)
        s[i] = '-';

    if(n/10){
    s[i++]= n % 10 + '0';
    itoaRecursivo(n/10,i);
    }
     
    s[i] = '\0';
    printf("%s"" ",s);

    /*reverse(s);
      printf("%s\n ",s);*/
}

void reverse(char s[]) {
    int c, i, j;
    for ( i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
