/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.6 */

/* El siguiente programa reescribe las funciones getline,itoa,atoi,reverse,strindex,getop
usando apuntadores en lugar de arreglos */
/* Consideramos una linea grande lineas de mas de 10 caracteres */

#include <stdio.h>
#include <string.h>

int getlinee(char *);
void reverse(char *s);
int strrindex(char *, char *);
void itoa1(int n, char *s);
void copy(char to[], char from[]);
void copyandiv(char to[], char from[]);
double atof(char *s);
// Imprime la line de entrada mas larga aceptando cualquier logintud de cadenas

main()
{
 int len;
 char line[100];

   len = getlinee(line);
   printf("\nLa linea es %s, su longitud %i\n",line,len);
 
   printf("Cadena invertida %s\n",line);
   reverse(line);
   printf("Cadena invertida %s\n",line);
   
   int n = -12;
   char s[10];

    printf("Entero :%i\n",n);
    itoa1(n,s);
    printf("Cadena :%s\n",s);
    
    printf("La 1ra ocurrencia de %s en %s tiene indice %i\n",s,line,strrindex(line,s));

    printf("La cadena %s como flotante es %f\n",s,atof(s));
   return 0;
}


// getline: Regresa la longitud de line

int getlinee(char *s)
{
  int c,i=0;

  while((c=getchar()) != EOF && c != '\n'){
    *(s+(i++)) = c;
  if (c == '\n')
    *(s+(i++)) = c;
  }

  *(s+i) = '\0';
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

/* invierte una cadena */
void reverse(char *s)
{
  int i,j,k;
  
    for(i=0,j = strlen(s)-1;i<j;i++,j--){
      k = *(s+i);
      *(s+i) = *(s+j);
      *(s+j) = k;
    }
}

/* funcion que convierte un entero a cadena s */

void itoa1(int n, char *s){
  int i,j,sign;
  
  if((sign = n) < 0) /* entero negativo */
    n = -n; /* Al volver el numero negativo en positivo tenemos como maximo un numero
	     2^(N-1) - 1, por lo tanto no alcanza la cota 2^(N-1) para negativos en C2*/
  i=0;
  do{
    *(s+(i++))=n%10 + '0';
  }while((n/=10)>0);
 
  if(sign < 0) /* vamos a modificar aqui con if((sign = n) < 0) y borrar lo anterior */
    *(s+(i++))='-';
    *(s+i)='\0';
  reverse(s);
}

/* strrindex : regresa el indice de t en s, -1 si no existe */
/* la posicion que entrega es la entrada de t mas a la derecha */
int strrindex(char *s, char *t)
{
int i,j,k;

for(i=strlen(s)-1;i > 0;i--){
for(j=i,k=strlen(t)-1;k!=0 && *(s+j) == *(t+k);j--,k--)
;
if(k == 0)
return j;
}

return -1;
}

/* La funcion atof que convierte una cadena a un numero flotante (double)*/
 
double atof(char *s){
  double val, power;
  int i, sign;

  for(i=0;isspace(*(s+i));i++)
    ;
  sign = (*(s+i) == '-') ? -1 : 1;
  if(*(s+i) == '+' || *(s+i) == '-')
    i++;
  for(val = 0.0; isdigit(*(s+i));i++)
    val = 10.0*val + (*(s+i) - '0');
  if(*(s+i) == '.')
    i++;
  for(power = 1.0;isdigit(*(s+i));i++){
    val = 10.0*val + (*(s+i) - '0');
    power *= 10.0;
  }
  return sign*val/power;
}
