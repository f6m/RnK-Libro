/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.20 */

/* Programa que extiende dcl() para que acepte argumentos de funciones como int p(int *, int *)
o int *p(char s, float k)
Obsercvacion: Los argumentos de funciones son nombre(tipo dcl)
Esto quiere decir que hay que modificar la gramatica y contemplar los argumentos de funciones recursivo

dcl -> optional *s dirdcl
dir -> name / (dcl) / name(optional pardcl) / name[optional tam] 
pardcl -> parmdcl, / dclspec / dcl
dclspec -> typespec / dclspec
typespec -> typequal / dclspec

Error: querer hacerlo en una solca funcion sin extender la gramatica: si no hay algo
construyelo.
./a.out
int p(int , int)
Tipo desconocido en la lista de parametros
Tipo desconocido en la lista de parametros
p: funcion que espera  int, int funcion que regresa int
*/

/* Precedencias mayor
1) parentesis agrupando partes de declaraciones
2) () para funciones y [] para arreglos
3) el simbolo * apuntador a */

/* dcl-dirdcl: Analizador sintactico por orden recursivo*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXTOKEN 100

/* Funciones para el manejo del buffer en el array */
int getch(void); //regresa el contenido del buffer o lee un caracter
void ungetch(int); //mete el caracter c al buffer

/* Funcion para obtener un token (una particula semantica) */
int gettoken(void);

/* Funcion para reconocer una declaracion complicada de apuntadores */
void dcl(void);
void dirdcl(void);

/* Funcion para reconocer la declaracion de los argumentos de funcion */
void paradcl(void);
void dclspec(void);
int typespec(void);
int typequal(void);
int compare(char ** , char **);


/* Funcion que del analizador sintactico*/
// void undcl(void);

/* enumeration NAME = 1, PARENS = 2, BRACKETS = 3 */
enum{NAME, PARENS, BRACKETS};
enum{NO, YES};

char token[MAXTOKEN];//cadena del ultimo token
char name[MAXTOKEN];//nombre del identificador
char datatype[MAXTOKEN];// tipo de dato = char, int, etc
char out[1000];//cadena de salida
int tokentype; //tipo token NAMBER PARENS BRACKETS
int prevtoken; 

int main(){ /*Convierte la declaracion inicial a palabras*/
  int type;
  char temp[MAXTOKEN]; /*Cadena de caracteres de tamaño MAXTOKEN*/

    while(gettoken() != EOF){ //Hace la 1ra llamada
      strcpy(datatype,token); /*Copia el 1er token en datatype*/
      out[0]='\0'; //out no contiene nada
      dcl();
      if(tokentype != '\n') //da la respuesta cuando llega el caracter nueva linea
	 printf("Error de sintaxis\n");
      if(datatype=='\0' || name=='\0' || out=='\0') //si no esta vacio datatype
     printf("Error: ids vacios\n");
      else  printf("%s: %s %s\n",name,out,datatype);
   }
  return 0;
}

/*
int main(){ //Convierte la declaracion inicial a palabras
  int type;
  char temp[MAXTOKEN]; //Cadena de caracteres de tamaño MAXTOKEN

    while(gettoken() != EOF){
      strcpy(out,token); //Copia la cadena en token en out
      while((type = gettoken()) != '\n')
	if(type == PARENS || type == BRACKETS)
	  strcat(out,token);
	else if(type == '*'){
	  sprintf(temp,"(*%s)",out);
	  strcpy(out, temp);
	}
	else if (type == NAME){
	  sprintf(temp,"%s%s",token,out);
	  strcpy(out,temp);
	}
	else printf(" entrada invalida en %s\n",token);
      printf("%s\n",out);
    }
  return 0;
} */

/* Funcion que modifica la cadena token en base a la lectura hecha de esta en la entrada
estandar, y regresa un int indicando el tipo de cadena leida: parentesis, corchetes o nombre.
Esta funcion ignora los blankos y tabs iniciales 
ENTRADA: nada
SALIDA: PARENS, BRACKETS, NAME, (, caracter leido c
SALIDA-MODIFICA: En estos casos char token[MAXTOKEN] es modificado: (),
gettoken() regresa el tipo de token o el caracter leido,  modifica token
gettoken() no borra el contenido de token[], solo el de su apuntador *p
*/

int gettoken(void)
{
  int c;
  char *p= token; /*define pointer *p and initialize to char array token[MAXTOKEN] */
  int str=0;
  /* function getch gets a char from standard input */ 
  while((c=getch()) == ' ' || c == '\t') /*ignore blanks and tab characters */
    ;
  if(c == '('){ /*Si encuentra un (*/
    if((c = getch()) == ')'){ /*reads following character and if it is ) */
	 strcpy(token,"()"); /* copy () to char array token */
	 return tokentype = PARENS;
       }
       else{ /* if the second character is not ) then save it in buffer and increases bufp */
	 ungetch(c); // si no es un caracter ) lo metes al buffer buf[bufp++], esperando encontrar otro posterio (dcl)
	 return tokentype = '('; /*regresa ( */
	 }
      }  
    else if(c == '['){ /*if character readed is [ */
      for(*p++ = c;isalnum(c = getch()) || c==']';) /* *(p++)=*p++,save [ in token[1] and increases pointer to next address, then read a character
   until user enters ] */
	{
         *p++=c;
	  //Si encuentra un [ recorre lo que hay dentro siempre que sea menor a 10 digitos y lo que encuentras es un numero o una letra 
        if (strlen(p)>10 && c!=']') {
	  *p='\0'; 
	  return tokentype = c;
	} //error pasaron 10 caracteres alfanum y no llego el ]
	if(c==']')
      	{
      	*p = '\0'; /* when find ] breaks for cycle and assign end character to string (char array) token */
      	return tokentype = BRACKETS;
		}
	}
      
    }
    else if(isalpha(c)){ /* if finds neither ( not [ but an character a,b,c...,z upper an lower */
      for(*p++ = c;isalnum(c = getch());) /*save alphanumeric in token[1] and continue reading andn saving while is aA or number*/
	*p++ = c;
      *p = '\0'; /* then assign final string character */
      ungetch(c); /* save last readed character */
      return tokentype = NAME;
    }
    else return tokentype = c; /* return strange character for gettoken */
  }


  #define BUFSIZE 100
  char buf[BUFSIZE]; //array de 100 chars 
  int bufp = 0; //

  /* getchar function, in case bufp > 0, decreases bufp and return buf[bufp], else obtain a character */
  int getch(void) //
  {
    return (bufp > 0) ? buf[--bufp] : getchar(); /* Si se incremento el indice el contenido de buf[--bufp]-uno antes, o getchar() (lee) */
  }

/* Function o simulate a FIFO a pile */
/* Para que?? estas funciones pueden declararse dentro de la funcion que las ocupa? */
  void ungetch(int c)
  {
    if (bufp >= BUFSIZE)
      printf("ungetch: demasiados caracteres \n");
    else
      buf[bufp++] = c; //mete el caracter c al buffer 
  }

/* function to count *s in order to recognize a declaration */
void dcl(void)
{
int ns;

for(ns = 0;gettoken()=='*';) /*llama gettoken 2da vez buscando * y los cuenta */
ns++;
dirdcl();
while(ns-- > 0)
  strcat(out," apuntador a "); /* concatenate string to char array out */
}

/* Funcion que reconoce un declarador directo dcl-directo */
void dirdcl(void)
{
  int type;
  if(tokentype == '('){ 
    dcl();
    if(tokentype != ')') // (dcl)
      printf("Error: Falta )\n");
  }
  else if (tokentype == NAME) //name() or name() or name(dcl,dcl,...,dcl)
    strcpy(name,token);
  else printf("Error: Se esperaba Nombre o (dcl) \n");
  while((type=gettoken()) == PARENS || type == BRACKETS || type == '(')  //name() or name() or name(dcl,dcl,...,dcl)
    if(type == PARENS)
      strcat(out," funcion que regresa");
    else if(type == '('){
        strcat(out,"funcion que espera ");
	paradcl(); //procesamos los parametros de la funcion
        strcat(out," funcion que regresa");
  }
    else{
      strcat(out," arreglo");
      strcat(out,token);
      strcat(out," de");
    }
}

// Parse en declaracion de parametros 
void paradcl(void) 
  {
   do { 
  dclspec();
  } while(tokentype == ',');
 if(tokentype != ')')
    printf("Falta ) en declaracion de parametros \n");
 } 

//
void dclspec(void)
{
char temp[MAXTOKEN]	;
temp[0]='\0';

gettoken();

do {
if(tokentype != NAME) {
prevtoken = YES;
dcl();
} else if(typespec() == YES){
strcat(temp," ");
strcat(temp,token);
gettoken();
} else if(typequal() == YES){
strcat(temp," ");
strcat(temp,token);
gettoken();
} else printf("Tipo desconocido en la lista de parametros\n");	
}while( tokentype != ',' && tokentype !=')');
strcat(out,temp);
if (tokentype == ',')
  strcat(out,",");
}

int typespec(void)
{
 static char *types[]={
"char",
"int",
"void",
"double",
};

char *pt=token;
if( bsearch(&pt, types, sizeof(types)/sizeof(char *), sizeof(char *), compare) == NULL)
return NO;
else return YES;
}

int typequal(void)
{
static char *typeq[]={
"const",
"volatile",
};
char *pt=token;
if( bsearch(&pt,typeq, sizeof(typeq)/sizeof(char *), sizeof(char *), compare) == NULL)
return NO;
else return YES;
}

//Para la busqueda binaria con bsearch()
int compare(char **s , char **t)
{
  return strcmp(*s,*t);
}

	  
	
      
