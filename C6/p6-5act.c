/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 6.5 */

/* Programa que muestra el uso de una funcion lookupdel para borrar (en base a un nombre) 
un nombre y una defnicion, es decir un bloque entero de la tabla en hashtab, es decir
borra la estructura completa nlist que contiene */

/* Obs1: La regla seria liberar la memoria asignada a cada elemento que llamo a malloc */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 5 //101 pero usamos 5 pare ver las coaliciones

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


static struct nlist *hashtab[HASHSIZE]; /* Tabla de apuntadores a estructuras nlist*/
unsigned hashindex[HASHSIZE];
int ind=0; //indice de para hashindex array

main(){
  struct nlist *f;
  // f=(struct nlist *) malloc(sizeof(*f));
  printf("El valor hash de ana es %4d\n",hash("ana"));
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
  imprimetab();
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
