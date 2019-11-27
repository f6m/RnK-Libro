/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.14 */

/* Programa que muestra una estadistica (histograma de frecuencias) de cada caracter leido en el la entrada estandard, analizando un maximo de size caracteres.*/

#include <stdio.h>
#define size 150
#define mword 150

main(){
  int c,i,j,max;
  int nchars[size];
  int nstats[mword];

// Inicializamos las entradas del archivo nwords a 0.
for(i=0;i<size;i++)
  {
    nchars[i]=0;
    nstats[i]=0;
  }

 i=0;
 while((c=getchar())!= EOF){
   /* Solo registramos los caracteres en el rango 0 - 126 */
   for(i=0;i<=126;i++)
     if(c == i)
       ++nchars[i];
 }

 /* Imprimimos las ocurrencias la estadistica de los caracteres */

 printf("\n Array of frecuency chars =\n");
 for(i=0;i<size+1;i++)
  printf("%d\t",nchars[i]);
 printf("\n");
 

 //Falta mostrar la estadistica del programa
 printf("\n Es histograma quiere decir ...\n");
 for(i=0;i<size;++i)
   {
           
          if(nchars[i] != 0)
	    printf("\n Hay %i caracteres del tipo %c:\t",nchars[i],i);
	   for(j=1;j<=nchars[i];j++)
	      printf("*");
   }
   printf("\n");
}
