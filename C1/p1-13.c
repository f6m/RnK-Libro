
/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.13 */

/* Programa que muestra una estadistica del las longitudes de las palabras ( tomadas de la entrada estandard, analizando un maximo de size palabras.*/


#include <stdio.h>
#define size 100
#define mword 100

main(){
  int c,i,j,max;
int nwords[size];
int nstats[mword];

// Inicializamos las entradas del archivo nwords a 0.
for(i=0;i<size;i++)
  {
    nwords[i]=0;
    nstats[i]=0;
  }

 i=0;
 while((c=getchar())!= EOF){
   /* --nwords[i] para evitar que cuente el caracter ' ' en el array */
   if (c == ' ' || c=='\n')
     {
       ++i;
       --nwords[i];
     }
   ++nwords[i];
 }

 max = i;

 printf("\n Array of frecuency words =\n");
 for(i=0;i<max+1;i++)
  printf("%d\t",nwords[i]);
 printf("\n");
 
 for(i=0;i<max+1;i++)
  {
	 for(j=1;j<mword;j++)
	   {
     if(nwords[i]==j)
       ++nstats[j-1];
	   }
       }


 //Falta mostrar la estadistica del programa
 printf("\n Es histograma quiere decir ...\n");
 for(i=0;i<size;++i)
   {
     //printf("\n palabras de tama~no %i \n",i+1);
     //for(j=1;j<nstats[i];++j){
     // putchar("a");
     //}
        
          if(nstats[i] != 0)
	    printf("\n Hay %i palabras de tama~no %i:\t",nstats[i],i+1);
	   for(j=1;j<=nstats[i];j++)
	      printf("*");
   }
 printf("\n");
}
