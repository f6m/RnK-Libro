/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 6.2 */


/* Programa que mediante un arbol binario AB (de busqueda) ordena y cuenta la ocurrencia de las palabras dadas por el teclado o en un archivo C que no sean palabras
reservadas, las compara hasta sus n primeros digitos y las ordena alfabeticamente, 

(1)las palabras no pueden ser palabras reservadas del lenguaje C

(2)No contar palabras dentro de cadenas constantes. 
Ejemplo:
$ ./a.out 4
"hola holah" /* adios adioss adiossss */
/* word es " 
 3 adios
 2 hola */

/* (3) No contar palabras dentro de comentarios */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *keytab[] ={
  "auto",
  "break",
  "case",
  "char",
  "const",
  "continue",
  "default",
  "do",
  "double",
  "else",
  "enum",
  "extern",
  "float",
  "for",
  "goto",
  "if",
  "int",
  "long",
  "register",
  "return",
  "short",
  "signed",
  "sizeof",
  "static",
  "struct",
  "switch",
  "typedef",
  "union",
  "unsigned",
  "void",
  "volatile",
  "while",
};

#define NKEYS 33
#define MAXWORD 100

struct tnode{ /* El nodo del arbol */
  char *word;/* apunta hacia la palabra */
  int count; /* numero de ocurrencias */
  struct tnode *left;  /* hijo izquierda */
  struct tnode *right; /* hijo derecho */
};


#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *,int); //agrega un nodo regresando un apuntador al tnode
void treeprint(struct tnode *); //imprime arbol
int getword(char *, int); //obtiene la palabra
int getword2(char *, int); //obtiene la palabra
int getch(void); //funcion que lee el caracter o saca del bufer
void ungetch(int); //mete al bufer
int finde(char []); //busca secuencialmente una palabraen el arreglo keytab de reservadas

/* Array para guardar una palabra */
char word[MAXWORD];

/* Conteo de frecuencia de palabras */

main(int argc, char *argv[]){
  struct tnode *root; //apuntador a una estructura
  int num,cd;

  printf("el tamaño de keytab[] es %i\n",NKEYS);
  printf("argc es %i\n",argc);
  if(argc == 1) //Si solo hay el nombre del programa como invocacion
    printf("Uso: programa numero\n");
  if(!isdigit(*argv[1])) //Si la bandera no es un digito
    printf("Parametro incorrecto %s\n",argv[1]);
    
  
  num = atoi(argv[1]); //convertimos a la entrada.
  printf("Numero de caracteres a comparar para la relacion de las palabras %d\n",num);

  root = NULL; //apuntador estructura
 
  while ((getword2(word, MAXWORD) != EOF)&&  ((cd = finde(word)) == 0)){
    printf("word es %s \n",word);
    printf("%s NO es palabra reservada\n",word);
    printf("el valor de cd es %i\n",cd);
	/*  for(i=0;(i < NKEYS ) && !(strcmp(keytab[i],word)) && isalpha(word[0]);i++)
	    root= addtree(root,word,num);*/
    if(isalpha(word[0])) //si empieza con una letra Aa,...,Zz 
	root = addtree(root,word,num);
      
  }
  	
  treeprint(root);
  return 0;
}

struct tnode *talloc(void);
char *strup(char *);

/* addtree: agrega un nodo con w, en o bajo p*/

struct tnode *addtree(struct tnode *p, char *w, int m) //Agregar
{
  int cond;
  
  if(p == NULL){ /* Llego una nueva palabra para la raiz */
    p = talloc(); //es una funcion para asignacion de memoria con malloc
    p->word = strup(w);
    p->count = 1;
    p->left = p->right = NULL;
  }else if((cond = strncmp(w,p->word,m)) == 0)
    p->count++; /*palabra repetida*/
  else if(cond < 0) /* menor, va contenido del subarbol izquierdo */
    p->left = addtree(p->left,w,m);
  else //mayor, va en el arbol derecho 
    p->right = addtree(p->right,w,m);
  return p;
}

/* Recorrido inorder del arbol */
void treeprint(struct tnode *p)
{
  if(p != NULL){
    treeprint(p->left);
    printf("%4d %s\n",p->count,p->word);
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

/* La funcion que obtiene las palabras */

int getword2(char *word, int lim)
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
 
/* Funcion finde que busca la ocurrencia de word en el array keytab de palabras reservadas */
int finde(char word[])
{
  int i,val,fin=0;
  
  for(i=0;i<NKEYS-1;i++){
    if((val = strcmp(keytab[i],word)) == 0)
      fin = 1;
  }

  return fin;
}
  
/* Falta eliminar la ocurrencia de palabras entre llaves */
