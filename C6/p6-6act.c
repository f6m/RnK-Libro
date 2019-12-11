/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 6.6 */

/* Programa que realiza un version simple de la directiva #define del preprocesador de C.

#define word defn

Idea:
1) buscar #define de la entrada estandar / archivo.c usar getword2.
2) buscar la directiva #undef y usar undef(previamente programada)
getword sirve para validar # define pero necesitamos #define
modificamos getword para crear getdefn
Obs: #define hola 
apaga la ocurrencia de hola es decir la omite del archivo.
3) por cada define crear una entrada en la tabla hash.
4) contemplar los errores de sintaxis al usar #define/undef

Obs1: sustituir word por su expresion defn (esto creo no es parte del preprocesador y requiere otro programa o enlazar esto).
Obs2: Falta revisar su funcionamiento del ultimo enter al final de la linea.
 
/* Obs1: La regla seria liberar la memoria asignada a cada elemento que llamo a malloc */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 5 //101 pero usamos 5 pare ver las coaliciones
#define MAXWORD 100 //el tamaño maximo de las palabras a buscar
/* La estructura basica */
struct nlist{
  struct nlist *next;
  char *name;
  char *defn;
};

unsigned hash(char *);
struct nlist *lookup(char *);
void undel(char *);
struct nlist *install(char *, char*);
char *strgdup(char *);
void imprimetab(void);

//funciones para la tabla hash
static struct nlist *hashtab[HASHSIZE]; /* Tabla de apuntadores a estructuras nlist*/
unsigned hashindex[HASHSIZE];
int ind=0; //indice de para hashindex array

//funciones para leer la palabra, directiva y definicion
int getword(char *, int);
int getp(char *, int);
int getdefn(char *, int);
int getch(void);
void ungetch(int);

main(){
  struct nlist *f;
   int c; //el caracter devuelto por getword
/* Array para guardar una palabra */
char word[MAXWORD];
char defp[MAXWORD];
char defn[MAXWORD];

while ((c=getp(defp, MAXWORD)) != EOF) //EOF = ctrl+d, rastrea todas las palabras.
{
if(c=='#' && strcmp(defp,"#define")==0){ //la palabra es #define
	if( isalpha(c=getword(word, MAXWORD)) ) //la palabra siguiente empieza con alfanum.
		{
	getdefn(defn,MAXWORD); //llamamos de nuevo para obtener la definicion de nameh
	install(word,defn);
	imprimetab();
	}
}    
else if(c=='#' && strcmp(defp,"#undef")==0) { //la palabra es #undef
	if( isalpha(c=getword(word, MAXWORD)) ) //la palabra siguiente empieza con alfanum.
		{
	undel(word);
	imprimetab();
	}
}
else if(c=='#' && (strcmp(defp,"#undef")!=0 || strcmp(defp,"#define")==0))	
    printf("La directiva del preprocesador NO es define / undef\n");
	} //end while busqueda de #define #undef	

  // f=(struct nlist *) malloc(sizeof(*f));
  /* printf("El valor hash de ana es %4d\n",hash("ana"));
  printf("El valor hash de ana es %4d\n",hash("aNa")); //Es una biyeccion???
  f=install("pil","HELLYPE");
  f=install("omar","HELLYPE");
  f=install("del","HP");
  f=install("try","TRATAR");
  f=install("G","100");
  printf("La tabla hash tiene %4d entradas, hay %d posibles indices\n ",ind,HASHSIZE);
  undel("b");
  imprimetab();
  undel("try");
  imprimetab();
  undel("try");
  imprimetab();	
  undel("omar");
  imprimetab(); */
  //printf("En la estructura name es %s defn es %s\n",f->name,f->defn);
}

/* hash - genera la clave a partir de la cadena, un indice para hashtab */
unsigned hash(char *s)
{
unsigned hashval;

for(hashval = 0; *s!='\0'; s++)
  hashval = *s + 31*hashval;
return hashval % HASHSIZE;
}

/*Funcion para imprimir la tabla hash: inprime coalisiones */
void imprimetab(void)
{
  int j; //apuntador al arreglo
 struct nlist *np;
 for(j=0;j < HASHSIZE; j++)
   {
     printf("%d ",hashindex[j]);
   for(np = hashtab[hashindex[j]];np != NULL;np = np->next)
     printf("[%s %s] -> ",np->name,np->defn);
   printf("\n");
   }
}

/*lookup : busca s en hashtab en una lista enlazada */

struct nlist *lookup(char *s){
  struct nlist *np;//apuntador a una estructura
  
  for(np = hashtab[hash(s)];np != NULL;np = np->next)
    if(strcmp(s,np->name)==0)
      return np; /*se encontro**/
  return NULL;/*no se encontro */
}


/*lookupde busca s en hashtab y la elimina */ 
/* si  hashtab[hash(s)] no es null apunta a una estructura struct nlist */
void undel(char *s)
{
  struct nlist *np,*tmp;
  int found=0;

  //usamos apuntador np para movernos (estandar) en la lista con enlace simple 
  for(np = hashtab[hash(s)];np != NULL;np = np->next){
    if(np->next!=NULL) //No revisa el ultimo
    if(strcmp(s,np->next->name)==0){ /* Encontro a s en el de adelante, la busqueda es secuencial */
  /*      free((void *) np->next); /*Libera el espaci en memoria asignado a np */
      found=1;
      tmp=np->next; /*Guardamos el apuntador en una apuntador temporal*/
      np->next=np->next->next; /*Hacemos que la el apuntador del bloque donde se encontro la palabra apunte al siguiente bloque */
      free(tmp->name); //borramos la memoria de name generada por install
      free(tmp->defn); //borramos la memoria de defn generada por install
      free(tmp);
  } else{ //estas en el ultimo campo de la lista enlazada
	if(strcmp(s,np->name)==0){ /* Encontro a s en el de adelante, la busqueda es secuencial */
	found=1;
      tmp=np; /*Guardamos el apuntador en una apuntador temporal*/
       /*Hacemos que la el apuntador del bloque donde se encontro la palabra apunte al siguiente bloque */
      free(np->name); //borramos la memoria de name generada por install
      free(np->defn); //borramos la memoria de defn generada por install
      np=NULL;
      free(np);
	} //fin-if
    } //fin-else
 }//fin for
  if(found==0) printf("En hashtab no existe la cadena %s\n",s);
} //fin undel

   
/*install : coloca (name, defn) dentro de hashtab */

struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;
  
  if((np = lookup(name)) == NULL){/*no fue encontrado*/
    np = (struct nlist *) malloc(sizeof(*np)); //genera memoria para el nodo completo
    if(np == NULL || (np->name = strgdup(name)) == NULL) //strgdup genero memoria para name
      return NULL;
    hashval = hash(name); //llave
    hashindex[ind++]=hashval; //guardamos el hash-indice-llave en un arreglo
    np->next = hashtab[hashval]; //hacemos que np-next apunta al arreglo con el indice llave
    hashtab[hashval] = np; //hacemos que hastab[val] apunte a np
  }else /*ya esta alli*/
    free((void *) np->defn); /*libera la anterior defn*/
  if((np->defn = strdup(defn)) == NULL) //tenero memoria para defn.
   return NULL;
 return np;
}
   
/* Funcion que crea un duplicado de s */
char *strgdup(char *s)
{
  char *p;
  p = (char *) malloc(strlen(s) + 1); /* +1 para '\0' */
  if(p!=NULL)
    strcpy(p,s);
  return p;
}

/* Funciones que manejan el buffer */

 #define BUFSIZE 100
  char buf[BUFSIZE];
  int bufp = 0;

  int getch(void)
  {
    return (bufp >0) ? buf[--bufp] : getchar();
  }

  void ungetch(int c)
  {
    if (bufp >= BUFSIZE)
      printf("ungetch: demasiados caracteres \n");
    else
      buf[bufp++] = c;
  }

//obtiene una palabra de la entrada E
int getword(char *word, int lim)
{
  int c,e;
  char *w = word;

    while(isspace(c = getch()) || c=='\t') /* ignora los espacios en blanco y tabs */
      ;
    if(c != EOF)
	*w++ = c;
    //if(!isalpha(c)){ //Si es la primer letra un Aa Bb..Zz
    // *w = '\0'; //Si no lo es agregamos \0 find e cadena
    // return c; //regresamos 
    //}
    if(c=='"')
      while((c=getch()) != '"') //avanza si es cadena constante, asumiento que no es solo un caracet "
	{if(c==EOF){printf("Error: faltan comillas derechas\n"); return c;}}
    if(c=='/' && (c=getch()) == '*')
	while((c=getch()) != '*' && (e=getch()) != '/')
	{if(c==EOF){printf("Error: faltan simbolos */ derechos\n"); return c;}}								 
    if(isalpha(c) || c=='_' || c=='"' || c=='/' || c=='%'){
    for(;--lim > 0;w++) //mientras lim aun sea positivo, incrementa el apuntador de word
      if(!isalnum(*w = getch())){ //es Aa...Zz | 0,..,9
	ungetch(*w); //si no lo es lo metems a buffer
	break; //rompes el ciclo for
      }
    } else { //
	 *w = '\0'; //Si no lo es agregamos \0 find e cadena
	 return c; //regresamos 
      }
    *w ='\0'; //fin de cadena
    return word[0]; //regresamos el apuntador a word su primera letra
}

//obtiene una palabra de la entrada E
int getp(char *word, int lim)
{
  int c,e;
  char *w = word;

    while(isspace(c = getch()) || c=='\t') /* ignora los espacios en blanco y tabs */
      ;
    if(c != EOF)
	*w++ = c;
    if(c!='#'){ //Si es la primer letra no es un #
    *w = '\0'; //Si no lo es agregamos \0 find e cadena
     return c; //regresamos 
    }
    //leemos lo que sigue despues de #
    if(isalpha(c=getch())){
	*w++=c;
    for(;--lim > 0;w++) //mientras lim aun sea positivo, incrementa el apuntador de word
      if(!isalpha(*w = getch())){ //es Aa...Zz | 0,..,9
	ungetch(*w); //si no lo es lo metems a buffer
	break; //rompes el ciclo for
      }
    } else { //
	 printf("La directiva del preprocesador es invalida\n");
	 *w = '\0'; //Si no lo es agregamos \0 find e cadena
	 return c; //regresamos 
      }
    
    *w ='\0'; //fin de cadena
    return word[0]; //regresamos el apuntador a word su primera letra
	
}

//obtiene una palabra dedfinitoria para #define E A que puede ser vacia
int getdefn(char *word, int lim)
{
  int c,e;
  char *w = word;

    if(isspace(c = getch())) /* ignora el primer espacio en blanco  */
      ;

    if(isspace(c = getch()) || c=='\t' || c=='\n') /* Si lo que sigue es blank, tab o fin de linea */
      {
	*w='\0';
	return word[0];

	}
    if(c != EOF)
	*w++ = c;
    
    
    //No importa si es alfanumerico o caracter la defn
    for(;--lim > 0;w++) //mientras lim aun sea positivo, incrementa el apuntador de word
      if(!isalpha(*w = getch())){ //es Aa...Zz | 0,..,9
	ungetch(*w); //si no lo es lo metems a buffer
	break; //rompes el ciclo for
      }
        
    *w ='\0'; //fin de cadena
    return word[0]; //regresamos el apuntador a word su primera letra
	
}
	
