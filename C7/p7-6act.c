/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 7.6 */

/* Programa que compara dos archivos, imprimiendo la primera linea en donde difieran*/
/* Dos lineas son distintas si difieren en  un caracter o espacio en blanco o tabuldaor, etc.*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 200
int num=0;

char lin1[MAXLINE];
  char lin2[MAXLINE];
/* Imprime archivos en stdout(panatalla), contandolos e indicando su inicio/fin */
main(int argc, char *argv[]){
  FILE *fp,*fq; //apuntadores a los archivos
  void filecopy(FILE *, FILE *);
  char * filecheck1(FILE *,FILE *); //Descide si son iguales si no imprime la primera linea distinto
  void filecheck2(FILE *,FILE *); //Descide si son iguales si no imprime la primera linea distinto
  char *prog = argv[0];
  char *l;
  if(argc == 1) /* Sin args copia la entrada estandar */
    filecopy(stdin,stdout);
  else if(argc = 3)
      if((fp = fopen(*++argv,"r")) == NULL){
	fprintf(stderr,"%s: no se puede abrir %s \n",prog,*argv); //imprime el error en la salida errstd
	exit(1);
      }
      else if((fq = fopen(*++argv,"r")) == NULL){
	fprintf(stderr,"%s: no se puede abrir %s \n",prog,*argv); //imprime el error en errstd
	exit(1);
      }
      else {
	if((l=filecheck1(fp,fq))!=NULL)
	  printf("#[%d] %s\n",num,l);
	fclose(fp);
	fclose(fq);
      }
  if(ferror(stdout)){
    fprintf(stderr,"%s: error al abrir stdout\n",prog);
    exit(2);
  }
  exit(0);
}

/* Funcion filecheck1: revisa si ifp difiere con el archivo ofp:
regresa el apuntador a la primer linea distinta, obtiene las lineas
con fgets*/

char *filecheck1(FILE *ifp, FILE *ofp)
{
  int k;
  if(fgets(lin1,MAXLINE,ifp)!=NULL && fgets(lin2,MAXLINE,ofp)!=NULL)
    {k=strcmp(lin1,lin2);num++;}
  else 	printf("No se logro obtener alguna linea\n");
  if(k!=0) return lin1;

  while(k==0) //lee la primera linea del archivo ifp y la pone en lin
	{
	if(fgets(lin1,MAXLINE,ifp) != NULL && fgets(lin2,MAXLINE,ofp) != NULL)
	  {k=strcmp(lin1,lin2);num++; if(k!=0) break;}
	if(fgets(lin1,MAXLINE,ifp) == fgets(lin2,MAXLINE,ofp) == NULL && k==0) 
	  {
	    printf("Archivos iguales\n");
	    return NULL;
	  }
	}
  return lin1; //si llega aqui no llegaron al null 
}

 /* Funcion filecheck1: revisa si ifp difiere con el archivo ofp:
regresa el apuntador a la primer linea distinta, usa la idea
de filecopy del libro */
void filecheck2(FILE *ifp, FILE *ofp)
{
  int c1,c2,k;
  while((c1 = getc(ifp)) != EOF && (c2 = getc(ofp)) == c1)
     if(c1=='\n'){
	++k;
	printf("Linea %d: PASS\n",k);
	}
   if(c1==EOF) printf("Archivos iguales \n");
   printf("Linea  %d Caracter %c distinto\n",k,c1);
}

void filecopy(FILE * ifp, FILE *ofp){
  int c;
  while((c=getc(ifp))!=EOF)
    putc(c,ofp);
}




  
