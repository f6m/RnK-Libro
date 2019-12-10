/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 3.2 */

/* Programa que cuenta identifica los finales de linea (\n), tabuladores (\t)
secuencias de escape y los escribe como su representacion \n,\t,\r,\a,\",\\ */

/* Esto mientras copia cadena t a s */

/* Escribimos la funcion inversa que a partir de \n,\t, y secuencias de escape
lo convierta a su representacion*/

#include <stdio.h>
#include <string.h>
#define MAX 10000

void escseqtext(void);
void escseqc(void);

char text[MAX];
char prog[MAX];

main(){
  int c;
  int i=0;

  while((c = getchar()) != EOF)
        {
	  text[i++]=c;
	}
	
  printf("Cadena1:%s\n",text);
  escseqtext();
  printf("Cadena1 Convertida:%s\n",text);
  
  i=0;
  while((c = getchar()) != EOF)
        {
	  prog[i++]=c;
	}
	
  printf("Cadena2:%s\n",prog);
  escseqc();
  printf("Cadena2 Convertida:%s\n",prog);
} 

void escseqc(void)
{
  extern char prog[MAX];
  int i,j;
  
  for(i=0;i<=strlen(prog);i++)
  {
      if(prog[i]=='\\'){
	printf("Caracter: %c\n",prog[i]);
	switch(prog[i+1])
	    {
	    case 'a': prog[i]='\a';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case 'b': prog[i]='\b';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case 'f': prog[i]='\f';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case 'n':prog[i]='\n';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case 'r': prog[i]='\r';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case 't': prog[i]='\t';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case 'v': prog[i]='\v';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case '"': prog[i]='\"';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case '\\': prog[i]='\\';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case '\'': prog[i]='\'';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case '\?': prog[i]='\?';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case '\ooo': prog[i]='\ooo';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    case '\xhh': prog[i]='\xhh';
		    for(j=i+1;j<strlen(prog),prog[j]=prog[j+1];j++);
		    break;
	    
	    default: printf("El archivo no contine secuencias de escape\n");
		    break;  
	    } /* switch */
    } /* if */
   
  } /* for */
} /* escseqc */

void escseqtext(void)
{
  extern char text[MAX];
  int i,j,n;
  
  n=strlen(text);
  printf("Longitud Cadena: %i\n",n);
  
  for(i=0;i<=n;i++)
  {
      
	switch(text[i])
	    {
          printf("Caracter: %c\n",text[i]);
	     case '\a':text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='a';
		    break;
	     case '\b':text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='b';
		    break;
	     case '\f':text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='f';
		    break;
	    case '\n':text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j]
		    text[i+1]='n';
		    break;
	    case '\r': text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='r';
		    break;
	    
	    case '\t':text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j];
		    printf("Cadena actual: %s\n",text);
		    text[i+1]='t';
		    break;
	    case '\v':text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j];
		    printf("Cadena actual: %s\n",text);
		    text[i+1]='v';
		    break;
	    case '\?': text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='?';
		    break;
	    case '\'': text[i]='\\';
		    for(j=n+1;j>i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='\'';
		    break;
	    	    
	    case '\"': text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='"';
		    break;
	    case '\\': text[i]='\\';
		    for(j=n+1;j>i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='\\';
		    break;
	    case '\ooo': text[i]='\\';
		    for(j=n+1;j>=i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='\ooo';
		    break;
	    case '\xhh': text[i]='\\';
		    for(j=n+1;j>i+1;j--)
		      text[j+1]=text[j];
		    text[i+1]='\xhh';
		    break;
	    
	    default: printf("El archivo no contine secuencias de escape\n");
		    break;  
	    } /* switch */
     } /* for */
} /* escseqtext */
