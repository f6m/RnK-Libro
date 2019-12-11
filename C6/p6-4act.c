/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 6.4 */


/* Programa que mediante un arbol binario AB (de busqueda) imprime la ocurrencia de TODAS las palabras
de un archivo ordenadas conforme a la frecuencia de aparicion, la impresion sigue
el formato:

 "frec pal" */

/* 1) se genera el arbol con las palabras y las ocurrencias.
2) se almacena en un vector los apuntadores al arbol con un recorrido insort de AB.
3) se ordena el vector
/* (1) contaremos: blancos, tabuladores, nuevas lineas y otros caracteres */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int lines=0; //comenzamos con linea 1, numero de lineas \n que aparecen en el texto
int blanks=0; //contamos blancos
int tabs=0; //contamos tabuladores

#define NKEYS 33
#define MAXWORD 100
#define MAXWORDS 100000
#define MAXLINES 100
#define BUFSIZE 100

  char buf[BUFSIZE];
  int bufp = 0;

struct tnode{ /* El nodo del arbol */
  char *word;/* apunta hacia la palabra */
  int wc;
  struct tnode *left; /* hijo izquierda */
  struct tnode *right;/* hijo derecho */
};

struct tnode *words[MAXWORDS]; //arreglo de apuntadores a estructuras tnode

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *); //agrega un nodo regresando un apuntador al tnode
void treeprint(struct tnode *); //imprime arbol
int getword(char *, int); //obtiene la palabra
int getword2(char *, int); //obtiene la palabra
int getch(void); //funcion que lee el caracter o saca del bufer
void ungetch(int); //mete al bufer
int compare(char **, char **); //Funcion de comparacion para usar en bsearch
void tree2vector(struct tnode *); //cuarda los apuntadores a los nodos del arbol en un vector
void sortvector(void); //cuarda los apuntadores a los nodos del arbol en un vector

/* Array para guardar una palabra */
char word[MAXWORD];
int nt=0; //numero de nodos actual del arbol

/* Conteo de frecuencia de palabras */

main(int argc, char *argv[]){
  struct tnode *root; //apuntador a una estructura
  int num,cd;

  root = NULL; //apuntador estructura
 
  while (getword2(word, MAXWORD) != EOF){ //Solo que no se llege al fin del archivo
    printf("word es %s \n",word);
    
    /*  for(i=0;(i < NKEYS ) && !(strcmp(keytab[i],word)) && isalpha(word[0]);i++)
	    root= addtree(root,word,num);*/
    if(isalpha(word[0])) //si empieza con una letra Aa,...,Zz y no esta word en el arreglo de palabras prohibidas
	root = addtree(root,word);
    else if (word[0] == '\n') {
	lines++;
        printf("Nueva linea espacios # %d \n",lines); //incrementamos el numero de lineas
      }
    //if(*buf == '\n') { //buf me permite saber el ultimo caracter de la linea, revisar con espacios+\n
    //	 lines++; 
    //	 printf("Nueva linea buf # %d \n",lines); //incrementamos el numero de lineas
         //printf("Palabras actuales:\n"); 
	 //treeprint(root);
    // }
 }
  tree2vector(root); //cuarda los apuntadores a los nodos del arbol en un vector
  sortvector();	
  //treeprint(root);
  for(cd = 0;cd < nt; cd++)
	printf("%4d %s \n",words[cd]->wc,words[cd]->word);
  printf("%4d b %4d t  %4d l\n",blanks,tabs,lines);
  return 0;
}

struct tnode *talloc(void);
char *strup(char *);

/* addtree: agrega un nodo con w, en o bajo p*/

struct tnode *addtree(struct tnode *p, char *w) //Agregar
{
  int cond;
  
  if(p == NULL){ /* Llego una nueva palabra para la raiz */
    p = talloc(); //es una funcion para asignacion de memoria con malloc
    p->word = strup(w);
    p->wc = 1; //inicializamos el #word a 1
    p->left = p->right = NULL; //hijos nulos
  }else if((cond = strcmp(w,p->word)) == 0) //la comparacion ahora es con strcmp(s,t)
    { 
       p->wc++; /*palabra repetida*/
    }
  else if(cond < 0) /* menor, va contenido del subarbol izquierdo */
    p->left = addtree(p->left,w);
  else //mayor, va en el arbol derecho 
    p->right = addtree(p->right,w);
  return p;
}

/* Recorrido recursivo INORDER del arbol la palabra  */
/* hACER UN RECORRIDO BUSCANDO EL MAXIMO */
void treeprint(struct tnode *p)
{
  if(p != NULL){
    treeprint(p->left);
    printf("%4d %s\n",p->wc,p->word);
    treeprint(p->right);
 }
}

#include <stdlib.h>

/*talloc : crea un nodo*/

struct tnode *talloc(void)
{
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *strup(char *s){
  char *p;
  
  p= (char *)malloc(strlen(s)+1); /* +1 para '\0', reservamos memoria para la palabra */ 
  if(p!=NULL) //si la reservacion fue exitosa
    strcpy(p,s); //copiamos la cadena s en la direccion reservada
  return p; //devolvemos el apuntador a esa direccion
}

    
/* La funcion que obtiene las palabras */

int getword(char *word, int lim)
{
  int c;
  char *w = word;

    while(isspace(c = getch()))
      ;
    if(c != EOF)
	*w++ = c;
    if(!isalpha(c)){
      *w = '\0';
      return c;
    }

    for(;--lim > 0;w++)
      if(!isalnum(*w = getch())){
	ungetch(*w);
	break;
      }
    *w ='\0';
    return word[0];
}
//obtiene el ultimo caracter
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

/* La funcion que obtiene las palabras */

int getword2(char *word, int lim)
{
  int c,e;
  char *w = word;

  while((isspace(c = getch()) || (c=='\t')) && c!='\n') /* ignora los espacios en blanco y tabs y revisa si es \n */
      if(isspace(c)) blanks++; else tabs++;

    if(c != EOF)
	*w++ = c;

    //if(!isalpha(c)){ //Si es la primer letra un Aa Bb..Zz
    // *w = '\0'; //Si no lo es agregamos \0 find e cadena
    // return c; //regresamos 
    //}
    if(c=='\n') return c;
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
    return word[0]; //regresamos el apuntador a word su primera letra, por esta no detecta el \n
}

void tree2vector(struct tnode *p) //cuarda los apuntadores a los nodos del arbol en un vector
{
  if(p != NULL){
    treeprint(p->left);
    words[nt++]=p; //incrementa al mismo tiempo el numero de nodos, contandolos
    treeprint(p->right);
   }

}

//Selection sort para ordenar el vector 
void sortvector(void) //cuarda los apuntadores a los nodos del arbol en un vector
{
  int i,j,ord,tmp;
  for(i=0;i<nt;i++)
     {
	ord=i;
	for(j=i+1;j<nt;j++)
	{
	if(words[j]->wc > words[ord]->wc) //Si el que esta adelante es mayor
	ord=j;
	}
	//Swap
	tmp=words[i]->wc;
	words[i]->wc = words[ord]->wc;
	words[ord]->wc = tmp;
    }
}

//ordena el arbol de acuerdo a la frecuencia de cada palabra
//int sorttree(void)
//{
//char *pt=word;
//if( sort(&pt, notwords, sizeof(notwords)/sizeof(char *), sizeof(char *), compare) == NULL)
//return 0;
//else return 1;
//}

//Para la busqueda binaria con bsearch()
//int compare(char **s , char **t)
//{
// return strcmp(*s,*t);
//}
