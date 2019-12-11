/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.13 */


/* El siguiente programa tail, que imprime las últimas n líneas de su entrada. Por omisión, n es 10, digamos, pero puede modificarse con un argumento optativo, de modo que: tail -n   imprime las últimas n líneas. El programa debe comportarse en forma racional sin importar cuán poco razonable sea la entrada o el valor de n. El programa de manera que haga el mejor uso de memoria disponible; las líneas deben almacenarse como en el programa de ordenamiento de la sección 5.6, no en un arreglo de dos dimensiones de taño fijo*/


#include<stdio.h>
#include<stdlib.h>
#define MAX 1000

int readlines(char *lineptr[],int nlines);
void ultimaslin(char *lineptr[],int nlines,int n);
char *lineptr[MAX];

main(int cont, char *op[])
{
  int nlines,i=0,k=1,l,n1;
  char s1[100];

  for(k=1;k<cont;k++)
    {
      strcpy(s1,op[k]);
      l=strlen(s1);

      for(i=0;i<=l;i++)
	{
	  if(s1[i]!='-')
	    {
	      switch (s1[i])
		{
		case 'n':
		  printf("Cuantas líneas quieres que me copie?\n");
		  scanf("%d",&n1);
		  printf("Dame las lineas de entrada\n");
		  if((nlines=readlines(lineptr,MAX))>=0)
		    {
		      
		      printf("\nLas ultimas %d lineas son:\n",n1);
		      ultimaslin(lineptr,nlines,n1);
		      return 0;
		      
		    }
		  else
		    {
		      printf("error: entrada demasiado grande para ordenarla\n");
		      return 1;
		    }
		  break;
		}
	    }
	  else
	    ;
	}
    }

}
#define MAXL 1000   /*máx longitud de cualquier línea de entrada*/
int getlinea(char *,int);
char *allocc(int);
void afree(char *p);  /*almacenamiento libre apuntado por p*/

#define ALLOCS 10000    /*Tamaño del espacio disponible*/
static char allocbuf[ALLOCS];   /*Almacenamiento para allocc*/
static char *allocp=allocbuf;   /*siguiente posición libre*/

char *allocc(int n)   /*Regresa un apuntador a n caracteres*/
{
  if(allocbuf+ALLOCS-allocp>=n)
    {
      allocp+=n;
      return allocp-n; /*antigua p*/
    }
  else   /*no hay suficiente espacio*/
    return 0;
}

void afree(char *p)  /*almacenamiento libre apuntado por p*/
{
  if(p>=allocbuf && p<allocbuf+ALLOCS)
    allocp=p;
}

int readlines(char *lineptr[], int maxlines)   /*lee líneas de entrada*/
{
  int len,nlines;
  char *p,line[MAXL];

  nlines=0;

  while((len=getlinea(line,MAXL))>0)
    if(nlines>=maxlines || (p=allocc(len))==NULL)
      return -1;
    else
      {
	line[len-1]='\0';    /*elimina caracter nueva linea*/
	strcpy(p,line);
	lineptr[nlines++]=p;
      }
  return nlines;
}

void ultimaslin(char *lineptr[],int nlines,int n)
{
  int i;

  if (n<=nlines)
    {
      //for(i=(nlines-1);i>=(nlines-n);i--)
      for(i=(nlines-n);i<nlines;i++)
	  printf("%s\n",lineptr[i]);
    }
  else
    {
      printf("\nNo puedo imprimir solo %d lineas\n",nlines);
    }
}

int getlinea(char s[],int lim)
{
  int c,i=0;

  for(i=0;i<lim-1 && (c=getchar())!=EOF && c!='\n';i++)
    s[i]=c;

  if(c=='\n')
    {
      s[i]=c;
      ++i;
    }
  s[i]='\0';
  return i;
}
