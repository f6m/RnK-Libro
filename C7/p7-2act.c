/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 7.2 */

/* El siguiente programa imprime los caracteres no graficos como numeros octales y divide las lineas de caracteres mas largas de un programa 
en lineas mas cortas */

/* Los caracteres no graficos son ejemplo: blank , tab o newline y se revisan con isgraph()*/
/* Consideramos una linea grande lineas de mas de 10 caracteres */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 10000
int gettline(char line[]); //obtiene un linea de la entrada estandar
void copyandiv(char to[], char from[],int k); //divide la linea de entrada
void imprime(char line[]); //para imprimir la lina considerando los signos no graficos

main()
{
  int len, max, i;
  char line[MAXLINE];
  char longest[MAXLINE];

 max=0;
 while((len = gettline(line)) != EOF){
   //printf("la linea %i es  [%s] tiene longitud:%i\n",max,line,len);
   ++max;
 if (len > 20) //Hubo una linea con mas de 20 caracteres
   {
     printf("Hubo una linea con mas de 20 chars, sera dividida en 2\n");
     // Inserta el caracter de division en un espacio. para no interferir con las silabas de la palabra
     copyandiv(longest,line,20);
     //printf("La linea devidida es [%s] con longitud %i \n",longest,strlen(longest));
     imprime(longest);
   }
 else printf("%s\n",line);
 } //end-while
 return 0;
}


// getline: Regresa la longitud de line y almacena la linea de entrada en line

int gettline(char s[])
{
  int c,i=0;

  while((c=getchar()) != EOF && c != '\n'){
    s[i++] = c;
  if (c == '\n'){
    s[i++] = c;
  }
   }
  if(c == EOF) return c; //si llegamos al final del archivo regresamos el caracter EOF
  s[i]= '\0'; //caracter final de la cadena
  return i;
}

// copyanddiv: from es la cadena larga y en to se colocara la division
// k indica el numero de caracteres para la sublinea
void copyandiv(char to[], char from[], int k)
{
  int i;
  char tmp[MAXLINE];
  int numl;
  numl=strlen(from) / k; //parte entera
  //i=0;
  //while((*(tmp + i) = from[i]) != '\0') //copia from en tmp y al mismo tiempo compara si no se llega al final
  //	++i;
  strcpy(tmp,from);
  for(i=k;i<strlen(from);i+=k){ //puntos divisorios, se pasa al dividir
    while(tmp[i]!=' ' && tmp[i]!='\n') //mientras no sea blanco
    i++; //...incrementa
  tmp[i] = '\n'; //cuando llegaste al blanco remplazalo en el temporal por nueva linea
  } //end for
  //while((*(tmp+(i+1)) = from[i]) != '\0') //vuelve a copiar from desde el punto de insercion \n en tmp
  //	++i;
  i=0;
  while((*(to+i) = tmp[i]) != '\0') //finalmente copia tmp en to. entonces en to esta la cadena dividida
	++i;
}


// imprime linea

void imprime(char line[])
{
//printf("el caracter dde ESPACIO tiene numero %i\n",'\t');
  int i;
  for(i=0;i<strlen(line);i++)
    //printf("el caracter %i es %c\n",i,i);
    if(isgraph(line[i])==0 &&  line[i]!='\n') /* Los caracteres no graficos aquellos < 33 y > 127*/
     //printf("El caracter %i en octal es %o\t",longest[i],longest[i]);
      printf("%.3o ",line[i]); //tres campos en octal
    else printf("%c",line[i]); //imprimimos solo el caracter
 /* }
 printf("\n");*/
}
