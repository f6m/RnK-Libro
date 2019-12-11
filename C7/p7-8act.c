/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 7.8 */


/* Programa que imprime un conjunto de archivos, iniciando cada nuevo
archivo en una pagina nueva, con un titulo y un contador de pagina por cada archivo
*/

/* una pagina esta definida por un numero fijo de lineas LINEPAGE */

/* Un conjunto de archivos tomados con los parametros argc/argv e imprime cada uno por pantallas */
/* Funcion getline que obtiene un linea la almacena en s y tiene longitud maxima lim */

#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define LINEPAGE 40 //40 lineas por pagina en cada archivo

//find: imprime lineas que coinciden con el patron del 1er. argumento */
/* Imprime archivos en stdout(panatalla), contandolos e indicando su inicio/fin */
main(int argc, char *argv[]){
  char line[MAXLINE];
  char patr[MAXLINE];
  long lineno = 0;
  int fileno = 0;
  int pageno = 0;
  int c, except = 0, number = 0, found = 0;
  FILE *fp;

  if(argc > 1) //hay archivos
   while(--argc > 0 && (fp=fopen(*++argv,"r"))!=NULL){
     fileno++;lineno=1,pageno++;
     printf("Archivo %d Pagina %d\n",fileno,pageno);
      while(fgets(line,MAXLINE,fp) != NULL){
	lineno++;
	if((lineno % LINEPAGE == 0)!=except)
	  {printf("Pagina %d \n %s",pageno++,line);}	
	else printf("%s",line);
	} //end while getline
    }//end while fopen
  else printf("Uso: prog file1 file2 filen \n");
} //end main


/* 
  FILE *fp;
  void filecopy(FILE *,FILE *);
  char *prog = argv[0];
  int num;
  
  num = 1;
  if(argc == 1) /* Sin args copia la entrada estandar */
//    filecopy(stdin,stdout);
/*  else
    while(--argc > 0)
      if((fp = fopen(*++argv,"r")) == NULL){
	fprintf(stderr,"%s: no se puede abrir %s \n",prog,*argv);
	exit(1);
      }
      else {
	/* Indica y cuenta en que parte inicia un nuevo archivo */
/*	printf("Archivo numero %i \n",num++);
	filecopy(fp,stdout);
	fclose(fp);
      }
  if(ferror(stdout)){
    fprintf(stderr,"%s: error al abrir stdout\n",prog);
    exit(2);
  }
  exit(2);
}

/* Funcion filecopy copia el archivo ifp al archivo ofp */
/*
void filecopy(FILE *ifp, FILE *ofp)
{
  int c;
  while((c = getc(ifp)) != EOF)
    putc(c,ofp);
} */
