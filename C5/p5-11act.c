/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.11 */

/* Programa que modifica las funciones entab, detab del capitulo 1.

Primero detab debe usar argc,argv para leer la entrada y leer un entero 
que significa el punto donde inician tabuladores (pueden ser mas de uno)

Segundo entab hace su misma funcion pero leyendo puntos de entrada y remplazando
caracteres formados por espacios en blanco por su correspondientes tabuladores y 
espacios en blanco hasta el siguiente paro de tabulacion. 

Utilizamos Ctrl + D para indicar el EOF
compilamos con gcc -o p p1-20.c -lm */

/* detab: Escriba un programa detab que reemplace tabuladores de la entrada con el número 
apropiado de blancos para espaciar hasta el siguiente paro de tabulación. Consideremos
un conjunto fijo de paros de tabulaciones, digamos cada n columnas. ¿Debe ser n una 
variable o un parametro simbolico? Aqui se refiere cona que los textos
suelen separarse en columnas, por ejemplo textos en dos columnas, etc. mismas que son
usualmente remplazadas por tabuladores*/

/* entab: Escriba un programa entab que reemplace cadenas de blancos por el mínimo número de 
tabuladores y blancos para obtener el mismo espaciado. Considere los paros de tabulación de 
igual manera que para detab. Cuando un tabulador o un simple espacio en blanco fuese suficiente
 para alcanzar un paro de tabulacion, ¿a cuál se le debe dar preferencia? */

#include <stdio.h>
#include <string.h>

void copy(char to[], char from[]);
void blanksij(char to[], int in,int fi);
void detab(char *, int *, int);
void entab(char *, int *, int);

char s[100],sb[100];

  int main(int argc, char *argv[]){
  int i,j,k,m,r;
  // char s[' ']="i          j          k",sb[' '],tmp[' '];
  // char s[' ']=,sb[' '],tmp[' '];
  int c,col,blanks;
  int points[' '];

  for(i=0;i<=argc-1;i++)
	points[i]=atoi(argv[i]);
 i=0;
 while((c = getchar()) != EOF)
 {
    s[i++]=c;
 }

 printf("La cadena actual es:%s y su longitud: %i\n",s,strlen(s));
 printf("Numero de argumentos: %i\n",argc); 
 //detab(s,points,argc);
 //printf("La cadena actual con # en lugar de tabs es:%s \n Longitud: %i\n",sb,strlen(sb));
 entab(s,points,argc);
 printf("La cadena actual con 1 tab por 6  blancos es:\t %s \n Longitud es: %i\n",s,strlen(s));
}

/*
detab: recibe una lista de puntos de tabulacion, por ejemplo 10, s[10] tiene un tabuldador
los tabuladores se remplazan por espacios en blanco (u otro caracter). Esta lista
se envia en la linea de comandos, si no se envia se considera la inspeccion en los tabuladores */

void detab(char *s, int *p, int l)
{
  int espacios,colum,i,j,w,ban;

  colum=0;
  if (l==1){
    for(i = 0;i<=strlen(s);i++)
      if(s[i]=='\t'){
	espacios = 8 - colum % 8;
	for(j = 0; j<espacios; ++j)
	 {strncat(sb,"#",1);putchar('#');}
	colum = colum + espacios;
      } else{
	//sb[i+espacios]=s[i];
        strncat(sb,&s[i],1);
	putchar(s[i]);
	colum = colum + 1;
	if(s[i]=='\n')
	  colum = 0;
      }
  }
  if(l>1){
    for(i = 0;i<=strlen(s);i++){
      ban = 0;
      for(j=1;j<l;j++){
       if(i==p[j]-1){ //se llego al punto de tabulacion
	espacios = 8 - colum % 8;
	for(w = 0; w<espacios; ++w)
	  {strncat(sb,"#",1);putchar('#');}
	colum = colum + espacios;
	ban=1;
	  }
      } //for
       if(ban==0){
       strncat(sb,&s[i],1);
	putchar(s[i]);
	colum = colum + 1;
	if(s[i]=='\n')
	  colum = 0;
     } //else
    } //for
  } //if
  }

/*
entab: recibe una lista de puntos de tabulacion, por ejemplo 10, s[10] tiene un tabuldador
los tabuladores se remplazan por espacios en blanco (u otro caracter). 
*/
void entab(char *s, int *p, int l)
{
  int m,j,i,w;
  if(l==1){
  for(j=0;j<strlen(s);j++)
    {
      printf("para j = %d tenemos s[%d]= %c\n",j,j,s[j]);
      if(s[j]==' ')
      {  
	m=0;     
	for(i=j;s[i]==' ';i++)//Continuan los espacios en blanco..
	{
	++m;
	}
	if(m<8){
	  printf("Hay menos de 8 blancos en este bloque---> lo dejamos con blancos\n");
	}
	printf("El numero de espacios en blanco en este bloque es: %d con indices (%d,%d) \n",m,j,j+m);
      if(m>=8)
	{
	printf("Hay almenos 8 blancos\n");
        blanksij(s,j,j+m);
        //printf("nos moveremos a la posicion %d\n",j);
	}
      }//if blanco
    } //for
	} //if 1 parameter
  if(l>1)
    {
      for(j=0;j<strlen(s);j++)
    {
      printf("para j = %d tenemos s[%d]= %c\n",j,j,s[j]);
      for(w=0;w<=l;w++){
      if(j==p[w] && w<=l)
      {  
	m=0;     
	for(i=j;s[i]==' ';i++)//Continuan los espacios en blanco..
	{
	++m;
	}
	if(m<8){
	  printf("Hay menos de 8 blancos en este bloque---> lo dejamos con blancos\n");
	}
	printf("El numero de espacios en blanco en este bloque es: %d con indices (%d,%d) \n",m,j,j+m);
      if(m>=8)
	{
	printf("Hay almenos 8 blancos\n");
        blanksij(s,j,j+m);
        //printf("nos moveremos a la posicion %d\n",j);
	}
      }//if punto de blanco
      }//for w
    } //for
    }
   } // fin entab
 
 
// Inserta los blancos y tabuladores necesarios para cubrir
// un bloque de blancos a partir de dos indices in y fi

void blanksij(char *to, int in, int fi)
{
  int n,i,j,b,r=0;
  char tmp[100];
  
  n=(fi-in)/8;
  b=(fi-in)%8;
  printf("el numero de tabs a insertar es %d y sobran %d blancos \n",n,b);
  
  //guarda en tmp la subcadena despues del intervalo a insertar tabs
   for(j=fi;j<=strlen(to);j++)
  {
    tmp[r++]=to[j];
  }
  printf("la cadena despues del bloque de blancos es %s\n",tmp);
 
  //agregamos los tabs indicados con el caracter * en sb
  for(i=0;i<n;i++)
  {
    to[in+i]='*';
  }
  
  to[in+n+b]='\0'; //agregamos el fin de archivo a la cadena sb modificada
  printf("La primera parte de la cadena es %s\n",to);
  strcat(to,tmp); //la unimos la primera parte y la segunda
}
 
// copy: copia 'from' en 'to'; supone que to es suficientemente grande
void copy(char to[], char from[])
{
  int i;

  i=0;
  while((to[i] = from[i]) != '\0')
	++i;
}

