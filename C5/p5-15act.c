/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.15 */

/* Programa que ordena lineas de entrada ya sea normal o de manera numerica, en este programa se ha agregado el parametro */
/* -r (de reverse) para poder ordenar de orden inverso y -d (de directorio) para poder comparar solo letras numeros y blancos en las lineas. */
/* El programa debe ser capas de aceptar banderas compatibles como -rd -rdn etc */
/* -r es reverse, -n es que son numeros, -d es que es directorio*/
/* -r sin -h ordena de forma inversa cadenas lexicograficamente*/
/* ./a.out -rn */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> /* stdlib incluye atof y una version de qsort po lo cual renombramos nuestra funci\'on qsortt */

#define MAXLINES 5000 /* # max de linas a ordenar */
char *lineptr[MAXLINES]; /* arreglo de apuntadores a char / cadenas */

int readlines(char *lineptr[], int nlines); /**lineptr[] arreglo de apuntadores*/
void writelines(char *lineptr[], int nlines);
void writelinesfloat(char *lineptr[], int nlines);

/* Declaracion de que acepta en sus parametros 
un apuntador a una funcion de comparación: numcmp compara cadenas que toma como numeros, o una parte como numeros, asume */
/* que la linea tiene numeros y los ordena de forma creciente, numcmprev lo mismo pero de forma decreciente, la 
funcion strcmp compara dos cadenas caracter por caracter, la funcion white ordena en termino de */
void qsortt(void *lineptr[],int left, int right,
	   int (* comp)(void *, void *));

int numcmp(char *, char *);
int white(char *, char *);
int numcmprev(char *, char *);
int strcmprev(char *, char *);

/* Ordena lineas de entrada un numero entero y un arreglo de apuntadores */
main(int argc, char *argv[]){
  int nlines,c;
  int numeric = 0; /* 1 si es ordenamiento numerico */
  int directory = 0; /* 1 si es ordenamiento de directorio */
  int reverse = 0; /* 1 si es ordenamiento en modo inverso */
  int maymin = 0; /* 1 para indicar que ingnore la comparacion entre mayusculas y minusculas */
  
  /*Bloque para verificar las entradas argv */
  /* (*++argv) avanza sobre las cadenas incrementando las direcciones y sacando su contenido */
  /* finalmente  verificamos si el primer caracter de cualquier parametro empezando por el segundo es '-' */
  while(--argc > 0 && (*++argv)[0] == '-') //++ avanza en el arreglo [0] da la primera posicion del apuntador, * el caracter.
    while( c = *++argv[0] ) /* avanzamos en los caracteres de la entrada que comienza con '-' */
      switch(c){
      case 'n': numeric =1;break;
      case 'd': directory=1;break;
      case 'r': reverse=1;break;
      case 'f': maymin=1;break;
      default: printf("Opcion ilegal %c\n",c);argc=0;break;
      }
  
  /* Condiciones si hay almenos dos parametros de entrada
 y si el parametro argv[1] es la bandera -r */   

 /* if(argc > 1 && strcmp(argv[1], "-n") == 0)
    numeric = 1;
  if(argc > 1 && strcmp(argv[1], "-d") == 0)
    directory = 1;
  if(argc > 1 && strcmp(argv[1], "-r") == 0)
    directory = 1; */
  
  if((nlines = readlines(lineptr, MAXLINES)) >= 0){ //lineptr es una varible global, 5000
    writelinesfloat(lineptr,nlines);
    if(directory == 1){ //-d
      printf("Orden de directorio basado en isalnum,blancos y \0 \n");
    qsortt((void **)lineptr,0,nlines-1,(int (*)(void*,void*))(white));
    }
    else
    if(reverse == 1 && numeric == 1) /* -rn o -r -n */
      {
      printf("Orden Numerico Inverso 9,..,0\n");
     qsortt((void **)lineptr,0,nlines-1,(int (*)(void*,void*))(numcmprev)); //(void **) apuntador a apuntadores
      }
     if(reverse == 1) /* -r only reverse strings lexicograficamente */
      {
      printf("Orden Inverso z,..a\n");
      qsortt((void **)lineptr,0,nlines-1,(int (*)(void*,void*))(strcmprev)); //(void **) apuntador a apuntadores
      }
     if(maymin == 1) /* -f compara a y A como iguales,ordena strings lexicograficamente */
      {
      printf("Orden Mayuscula/Minuscula  Zz,..Aa\n");
      qsortt((void **)lineptr,0,nlines-1,(int (*)(void*,void*))(strcasecmp)); //(void **) apuntador a apuntadores
      }    
 else
    qsortt((void **)lineptr,0,nlines-1,(int (*)(void*,void*))(numeric ? numcmp:strcmp));
    writelines(lineptr,nlines);
    return 0;
  }
  else{
    printf("Entrada demasiado grande para ser ordenada\n");
    return 1;
  }
}

/* funcion qsortt recursiva: 
Entradas: *v[], un arreglo de apuntadores/cadenas de texto/lineas de archivo
	   left, right, indices izquierdo y derecho dentro de cada linea 
	   (*comp)(void *, void*) un apuntadora a una funcion que acepta dos
	   parametros apuntadores a void */
void qsortt(void *v[], int left, int right, int (*comp)(void *, void *))
{
  int i, last;
  void swap(void *v[], int, int); /* Funcion de intercambio de dos entradas en el arreglo *v */

  if(left >= right) /* No hace nada si el arreglo contiene menos de dos elementos */
    return; /* regresa el control */
  swap(v, left, (left + right)/2); /* intercambia el primer elemento con el de la mitad */
  last = left; 
  for(i = left + 1; i <= right; i++) /*recorre desde la izquierda hasta la derecha */
    if((*comp)(v[i],v[left]) < 0) /* Los valores adelante del indice left se comparan con v[left], usualmente v[i] < v[left] */
      swap(v, ++last, i); /* Si v[i] < v[left] cambiamos v[left+1] <--> v[i] e incrementamos left para que el proximo cambio se realize en la siguiente posicion */
  swap(v, left, last); /* Caso contrario v[i] >= v[left] intercambiamos con el ultimo valor que realizamos */
  qsortt(v, left, last-1,comp);
  qsortt(v,last+1,right,comp);
}

 #include <math.h>

/*numcmp: compara s1 y s2 numericamente */
int numcmp(char *s1, char *s2)
{
  double v1, v2;
  v1 = atof(s1); /* convierte la string apuntada por s1 a double */
  v2 = atof(s2);
  if(v1 < v2)
    return -1;
  else if(v1 > v2)
    return 1;
  else
    return 0;
}
/*numcmprev: funcion para ordenar en forma descendente */
int strcmprev(char *s1, char *s2){
return -strcmp(s1,s2);
}
/*numcmprev: funcion para ordenar en forma descendente */
int numcmprev(char *s1, char *s2){
return -numcmp(s1,s2);
}

/* Funcion que compara numeros letras y blancos unicamente */
int white(char *s1, char *s2)
{
  int i,j,b1,b2;

  while(!isalnum(•s1) && *s1!=' ' && *s1 != '\0')
    s1++;

  for(i=0,j=0;i <= strlen(s1),j<= strlen(s2);j++,i++)
    {
      if(*(s1+i) == ' ')
	b1++;
      if(*(s2+j) == ' ')
	b2++;
      if(b1 < b2)
	return -1;
	else if(b1 > b2)
	  return 1;
	else
	  return 0;
    }
}
/* Intercambia dos datos */
void swap(void *v[],int i ,int j)
{
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

  #define MAXLEN 100

  int getlinea(char *, int);
  char *alloc(int);
  void afree(char *);
  
// Lee la linea hasta encontrar el caracter de nueva linea, 
// lim indica la longitud maxima de cada linea, devuelve su longitud
 int getlinea(char *s, int lim)
   {
    
     int c, i;
     i=0;
     while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
       s[i++] =c;
     if (c=='\n')
       s[i++] = '\0';//fin de la cadena
     s[i] = '\n';//caracter de salto
     return i;
   }


/* Lee las lineas de entrada */
int readlines(char *lineptr[], int maxlines){
   int len, nlines;
   char *p, line[MAXLEN];
 
   nlines = 0;
   while ((len = getlinea(line, MAXLEN)) > 0) //getline obtine una linea en el arreglo line y devueve su long.
     if(nlines >= maxlines || (p = alloc(len)) == NULL) //alloc almacena espacio para una cadena de longitud len
       return -1; //señal de que no se puede almacenar o sobrepasa el tamaño
     else{
       line[len-1] = '\0'; //fin de  la cadena
       strcpy(p, line); //copya line en p, el cual tiene suficiente espacio
       lineptr[nlines++] = p; //le asigna el apuntador a la primera linea lineptr aqui es local pero es global 
     }
   return nlines;
 }

/* Escribe las lineas */
 void writelines(char *lineptr[],int nlines)
   {
     int i;
     for(i = 0; i < nlines; i++)
       printf("%s\n",lineptr[i]);
   }

/* Escribe las lineas como flotantes*/
 void writelinesfloat(char *lineptr[],int nlines)
   {
     int i;
     for(i = 0; i < nlines; i++)
       printf("%i\n",atoi(lineptr[i]));
   }

	   
#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE]; //arreglo de caracteres
static char *allocp = allocbuf; //apuntador a un arreglo de caracteres


 char *alloc(int n) /* Regresa un apuntador a un segmento con n caracteres en allocbuf*/
   {
     if (allocbuf + ALLOCSIZE - allocp >= n){ //revisamos que la diferencia entre el fin (allocbuf + ALLOCSIZE) menos lo que hay (allocp) sea almenos n
       allocp += n; //incrementamos el apuntador n posiciones en allocbuf
       return allocp - n; //regresamos el apuntador al primer elemento para los n caracteres
     }else //no hay espacio
       return 0;
   }

 void afree(char *p) /* Almacenamiento libre apuntado por p*/
 {
   if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
     allocp = p;
 }
