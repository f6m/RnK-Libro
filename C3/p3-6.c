/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 3.6 */

/* El siguiente programa muestra el ejemplo de la funcion itoa la cual comvierte un numero entero a una cadena de caracteres */
/* Esta funcion usa tres argumentos: el entero, la cadena para almacenar la conversion, y un ancho minimo de campo */


#include <stdio.h>
#include <string.h>

void itoa(int, char [], int);
void reverse(char []);

main(){
  int x = 1345;
  char line[' '];

  itoa(x,line,10);
  printf("Entero %i Cadena = %s\n",x,line);
}



void itoa(int n, char s[' '], int min)
{
  int i, signo;
 
  if((signo = n) < 0)
    {
      n = -n;
    }
  i=0;
  do{
    s[i++] = n%10 + '0';
  }while((n/=10) > 0);

  if (signo < 0)
    s[i++]='-';
  s[i]='\0';
  while(i < min)
    s[i++] = ' ';
  reverse(s);
}

void reverse(char s[' '])
{
  int i,j,k;

    for(i=0,j = strlen(s)-1;i<j;i++,j--){
      k = s[i];
      s[i] = s[j];
      s[j] = k;
    }
}
