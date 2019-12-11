/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.12 */

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


/* Programa que extiende las funciones entab, detab de modo que acepten las
abreviaturas: 

entab -n +m
detab -n +m

o

entab 3 5 7
detab 5 9 12

o 

entab
detab

que indica puntos de tabulacion cada n columnas, iniciando en la columna m.
Seleccione el comportamiento por omision mas comveniente para el usuario */

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

  for(i=0;i<=argc-1;i++){
    if(argc > 1){
  if(*argv[1] == '-' && *argv[2] == '+' && argc == 3)
  {
    points[1] = atoi(&(*++argv)[1]); //n
    points[2] = atoi(&(*++argv)[1]); //m
	    points[argc]=0; //signal
	    break;
  }
  points[i]=atoi(argv[i]);
	  }
  }
 i=0;
 while((c = getchar()) != EOF)
 {
    s[i++]=c;
 }

 printf("La cadena actual es:%s y su longitud: %i\n",s,strlen(s));
 printf("Numero de argumentos: %i\n",argc); 
 detab(s,points,argc);
 printf("El texto actual con # en lugar de tabs es:\n%s \n Longitud: %i\n",sb,strlen(sb));
 //entab(s,points,argc);
 //printf("El texto actual con 1 tab = x blk es:\n %s \n Longitud es: %i\n",s,strlen(s));
}

/*
detab: recibe una lista de puntos de tabulacion, por ejemplo 10, s[10] tiene un tabuldador
los tabuladores se remplazan por espacios en blanco (u otro caracter). Esta lista
se envia en la linea de comandos, si no se envia se considera la inspeccion en los tabuladores
notmal. Si las banderas de ejecucion *argv[] usan el formato -n -m
Los tabuladores se remplazan por espacios en blanco (u otro caracter). Al llegar el fin de linea
debe repetir el mismo patron de tabs */

void detab(char *s, int *p, int l)
{
  int espacios,i,j,w,ban,lin;

  if (l==1){ // no hay parametros argv
    for(i = 0;i<=strlen(s);i++){
      if(s[i]=='\t'){
	espacios = 8; //- pos % 8; //8,7
	for(j = 0; j<espacios; ++j)
	 {strncat(sb,"#",1);putchar('#');}
      } else{
        strncat(sb,&s[i],1); //concatena el caracter
	putchar(s[i]);
      }
  }
  }
  if(l>1){
    lin = 0;
 if(l==3 && p[l]==0) // Soportamos tres parametros nombre -n=p[1] +m=p[2]
    {  
    for(i = 0;i<=strlen(s);i++){
      ban = 0;j=1;
   if(s[i]=='\n') {lin=i+1; printf("nueva linea en posicion: %i",i);printf("indices i, i-lin:%i %i\t",i,i-lin);}
      while(j <l){
      if(s[i]=='\n') j=1;
       if(i-lin==p[j]-1 || i-lin % p[j+1]==0){ //se llego al punto de tabulacion
	 espacios = 8; //- colum % 8;
	for(w = 0; w<espacios; ++w)
	  {strncat(sb,"#",1);putchar('#');}
	ban=1;
	  }
       j++;
      } //for
       if(ban==0){
       strncat(sb,&s[i],1);
	putchar(s[i]);
      } //else
    } //for
    }
 else{ //ha una lista de parametros
   lin=0;
   for(i = 0;i<=strlen(s);i++){
     ban = 0;j=1;
   if(s[i]=='\n') {lin=i+1; printf("nueva linea en posicion: %i",i);printf("indices i, i-lin:%i %i\t",i,i-lin);}
     while(j < l){ //varia j
       if(i-lin==p[j]-1 && s[i]=='\t'){ //se llego al punto de tabulacion
	 espacios = 8; //- colum % 8;
	for(w = 0; w<espacios; ++w)
	  {strncat(sb,"#",1);putchar('#');}
	ban=1;
	  }
       j++;
      } //while
       if(ban==0){
       strncat(sb,&s[i],1);
	putchar(s[i]);
      } //else
    } //for
  } //if
  
  }
}
/*
entab: una lista con las banderas de ejecucion *argv[] esperando el formato -n -m
Los tabuladores se remplazan por espacios en blanco (u otro caracter). Al llegar el fin de linea
debe repetir el mismo patron de tabs
*/
void entab(char *s, int *p, int l)
{
  int m,j,i,w, pos; //variable pos para considerar el salto de linea
  if(l==1){ //Comportamiento por defecto de estas funciones sin parametros -n +m y sin la lista p de puntos de tabulacion
    for(j=0;j<strlen(s);j++) //Considerar que si se llega al fin de la linea \n se tienen que repetir los tabs en la siguiente
    {
      printf("para j = %d tenemos s[%d]= %c\n",j,j,s[j]);
      pos = j;
      if (s[pos]=='\n') pos=0; //Salto de linea

      if(s[pos]==' ')
      {  
	m=0;     
	for(i=pos;s[i]==' ';i++)//Continuan los espacios en blanco..
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
        blanksij(s,pos,pos+m);
        //printf("nos moveremos a la posicion %d\n",j);
	}
      }//if blanco
    } //for
	} //if 1 parameter
  if(l>1){ 
  if(l==3 && p[l]==0) // Soportamos tres parametros nombre -n=p[1] +m=p[2]
    {
      
    for(j=0;j<strlen(s);j++) 
    {
      printf("para j = %d tenemos s[%d]= %c\n",j,j,s[j]);
      pos = j;
      if (s[pos]=='\n') pos=0; //Salto de linea

      if(pos==p[1] || pos % p[2]==0){ //si es n el resto de la division de j entre m es 0
	m=0;     
	for(i=pos;s[i]==' ';i++)//Continuan los espacios en blanco..
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
        blanksij(s,pos,pos+m);
        //printf("nos moveremos a la posicion %d\n",j);
	}
	}	
    }
    }
  else{ //no es el formato -n +m
      for(j=0;j<strlen(s);j++)
    {
      printf("para j = %d tenemos s[%d]= %c\n",j,j,s[j]);
      pos = j;
      if (s[pos]=='\n') pos=0; //Salto de linea
      for(w=0;w<=l;w++){
      if(pos==p[w] && w<=l)
      {  
	m=0;     
	for(i=pos;s[i]==' ';i++)//Continuan los espacios en blanco..
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
        blanksij(s,pos,pos+m);
        //printf("nos moveremos a la posicion %d\n",j);
	}
      }//if punto de blanco
      }//for w
    } //for
    } // else l==3
    } // if l>1
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

