/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.7 */

/* Programa que ordena lineas usando el algoritmo qsort y donde las lineas son obtenidas por medio 
de un arreglo pasado a readlines la funcion principal main(), eliminando el uso de alloc*/


#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

#define MAXLINES 5000
#define MAXC 1000
char str[100000]; /* arreglo de caracteres en lugar del buffer manejado por alloc/afree*/

char *lineptr[MAXLINES];

/* char str[MAXLINES][MAXC]; /* El arreglo doble donde almacenaremos la linea y que puede ser pasado como argumento a readlines */

/* Readlines con parametro y sin el **str ya que str es global */
int readlines(char *lineptr[], int nlines); 
void writelines(char *lineptr[],int nlines);
void qsort(char *lineptr[], int left, int right);

main(){
  int nlines; /* cuenta el numero de lineas leidas */

  if ((nlines = readlines(lineptr,MAXLINES)) >= 0){ 
    qsort(lineptr,0,nlines-1);
    writelines(lineptr,nlines);
    return 0;
  }else{
    printf("Error: entrada demasiado grande para ordenarla \n");
    return 1;
}
}

  #define MAXLEN 100

  int getlinee(char *s, int lim);
  void swap(char *v[], int i, int j);
  char *alloc(int);
  void afree(char *);
  
/* Funcion getline que obtiene un linea la almacena en s y tiene longitud maxima lim */
 int getlinee(char *s, int lim)
   {   
     int c, i;
     i=0;
     while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
       s[i++] =c;
     if (c=='\n')
       s[i++] = '\0';
     s[i] = '\n';
     return i;
   }

/* La función readlines tiene como parametros: el arreglo de apuntadores caracter, el tamaño maximo de 
   caracteres por linea, y conoce el arreglo str[] que ocuparemos en lugar de alloc, afree
   el hecho de pasar el arreglo de apuntadores como parametro modifica directamente dicho arreglo declarado
   de forma global */

int readlines(char *lineptr[], int maxlines){

   int len, nlines;
   char *p, line[MAXLEN];
   extern char str[]; /* este arreglo lo declare por primera vez de forma global fuera del main */
   p=&str[0]; /* p apunta a str[0] */
   
   nlines = 0; /* contador del numero de lineas */
   while ((len = getlinee(line, MAXLEN)) > 0) /* mientras leemos una linea */
     if(nlines >= maxlines) /* si la longitud el numero de lineas leidas es mayor a las permitidas */
   /* if(nlines >= maxlines || (p = alloc(len)) == NULL)*/
        return -1; /* devolver -1 */
     else{ 
      
       line[len-1] = '\0'; /* es redundante esta ? asignarle a la linea devuela por getline el caracter de fin de linea */
       strcpy(p,line); /* copia linea en line al arreglo str[nlines] */
       lineptr[nlines++] = p;       /* Asignacion de memoria y uso con str[100000] */
       p = p + len; /* p apunta a la dirccion del char de str en la posicion len */

     }
   return nlines; /* regresa el numero de lineas leidas */
 }


/*Funcion writelines que escribe las lineas ordenadas */
 void writelines(char *lineptr[],int nlines)
   {
     int i;
     for(i = 0; i < nlines; i++)
       printf("%s\n",lineptr[i]);
   }


/* Funcion qsort que ordena v[left]...v[right] en orden ascendente */
 void qsort(char *v[], int left, int right){

   int i, last;

   if (left >= right) /* No hace nada si el arreglo contiene menos de dos elementos */
     return;
   swap(v, left, (left + right)/2);
   last = left;
   for(i = left +1;i<=right;i++)
     if(strcmp(v[i],v[left]) < 0)
       swap(v, ++last,i);
   swap(v, left, last);
   qsort(v, left, last -1);
   qsort(v, last+1, right);
 }

 /* Función de intercambio de lineas */
 void swap(char *v[], int i, int j){
   char *temp;

   temp = v[i];
   v[i] = v[j];
   v[j]=temp;
 }

 #define ALLOCSIZE 10000
 static char allocbuf[ALLOCSIZE];
 static char *allocp = allocbuf;


 char *alloc(int n) /* Regresa un apuntador a n caracteres */
   {
     if (allocbuf + ALLOCSIZE - allocp >= n){
       allocp += n;
       return allocp - n;
     }else
       return 0;
   }

 void afree(char *p) /* Almacenamiento libre apuntado por p*/
 {
   if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
     allocp = p;
 }
