/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 6.3 */

/* Programa que mediante un arbol binario AB (de busqueda) ordena y cuenta la ocurrencia de las palabras 
dadas en un archivo y por cada palabra una lista de los numeros de linea donde aparece.

(2) Quitar ocurrencia de palabras como:
 
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int lines=0; //comenzamos con linea 1, numero de lineas \n que aparecen en el texto

#define NKEYS 33
#define MAXWORD 100
#define MAXLINES 100
#define BUFSIZE 100

  char buf[BUFSIZE];
  int bufp = 0;

struct tnode{ /* El nodo del arbol */
  char *word;/* apunta hacia la palabra */
  int countl[MAXLINES];/* List para los numeros de linea donde aparece la palabra */
  int indxl;
  struct tnode *left; /* hijo izquierda */
  struct tnode *right;/* hijo derecho */
};


#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *); //agrega un nodo regresando un apuntador al tnode
void treeprint(struct tnode *); //imprime arbol
int getword(char *, int); //obtiene la palabra
int getword2(char *, int); //obtiene la palabra
int getch(void); //funcion que lee el caracter o saca del bufer
void ungetch(int); //mete al bufer
int finde(char []); //busca secuencialmente una palabraen el arreglo keytab de reservadas
int notword(void); //Decide si la palabra actual es prohibida o no
int compare(char **, char **); //Funcion de comparacion para usar en bsearch



/* Array para guardar una palabra */
char word[MAXWORD];

/* Conteo de frecuencia de palabras */

main(int argc, char *argv[]){
  struct tnode *root; //apuntador a una estructura
  int num,cd;

  root = NULL; //apuntador estructura
 
  while (getword2(word, MAXWORD) != EOF){ //Solo que no se llege al fin del archivo
    printf("word es %s \n",word);
    
    /*  for(i=0;(i < NKEYS ) && !(strcmp(keytab[i],word)) && isalpha(word[0]);i++)
	    root= addtree(root,word,num);*/
    if(isalpha(word[0]) && (notword()==0)) //si empieza con una letra Aa,...,Zz y no esta word en el arreglo de palabras prohibidas
	root = addtree(root,word);
    else 
      if (word[0] == '\n') {
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
  	
  treeprint(root);
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
    p->indxl = 0; //inicializamos el indice del arreglo a 1
    p->countl[p->indxl]=lines; /*palabra repetida*/
    p->left = p->right = NULL;
  }else if((cond = strcmp(w,p->word)) == 0) //la comparacion ahora es con strcmp(s,t)
    { 
      if(p->countl[p->indxl] < lines)
	{
	p->indxl++;
	  p->countl[p->indxl]=lines; /*palabra repetida*/
	}
    }
  else if(cond < 0) /* menor, va contenido del subarbol izquierdo */
    p->left = addtree(p->left,w);
  else //mayor, va en el arbol derecho 
    p->right = addtree(p->right,w);
  return p;
}

/* Recorrido inorder del arbol la palabra  */
void treeprint(struct tnode *p)
{
  int i=0;
  if(p != NULL){
    treeprint(p->left);
    printf("%s ",p->word);
    while(i <= p->indxl)
      printf(" %4d",p->countl[i++]);
    printf("\n");
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
      ;
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

int notword(void)
{
 static char *notwords[]={
"a",
"de",
"en",
"el",
"es",
"eso",
"esto",
"de",
"la",
"o",
"son",
"un",
"una",
"y"
};

char *pt=word;
if( bsearch(&pt, notwords, sizeof(notwords)/sizeof(char *), sizeof(char *), compare) == NULL)
return 0;
else return 1;
}

//Para la busqueda binaria con bsearch()
int compare(char **s , char **t)
{
  return strcmp(*s,*t);
}
