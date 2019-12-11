/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 7.7 */


/* Programa que modifica el programa de busqueda de un patron del Cap 5
para que tome su entrada de un conjunto de archivos nombrados o, 
si no hay archivos nombrados como argumentos, de la entrada estandar.
¿Debe escribirse el nombre del archivo cuando se encuentra una linea que coincide?

R:si debe indicarse el archivo y la linea

/* patter finding program pag.127 */

/* Argumento optativo: -x -n 
-x imprimir todas las lineas exepto las que coincidan con el patron 
-n precede la linea su numero de linea 
uso find -x -n patron */

/* un conjunto de archivos tomados en los parametros argc/argv e imprime cada uno por pantallas */

/* Funcion getline que obtiene un linea la almacena en s y tiene longitud maxima lim */
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

//find: imprime lineas que coinciden con el patron del 1er. argumento */
/* Imprime archivos en stdout(panatalla), contandolos e indicando su inicio/fin */
main(int argc, char *argv[]){
  char line[MAXLINE];
  char patr[MAXLINE];
  long lineno = 0;
  int fileno = 0;
  int c, except = 0, number = 0, found = 0;
  FILE *fp;

  while(--argc>0 && (*++argv)[0] == '-')
	while(c=*++argv[0])
	switch(c){
	case 'x': except = 1;break;
	case 'n': number = 1;break;
	default: printf("find: opcion ilegal %c\n",c);
	argc=0;	found = -1; break;
	}
  if(argc < 2) //quedan dos el nombre del archivo y el patron
   printf("Uso: find -x -n patron file1 file2 filen \n");
  else {
    strcpy(patr,*argv++);
    while(--argc > 0 && (fp=fopen(*argv++,"r"))!=NULL){
      fileno++;lineno=0;
      while(fgets(line,MAXLINE,fp) != NULL){
	lineno++;
	if((strstr(line,patr)!=NULL)!=except){ //strstr localiza una subcadena en el archivo =)
	if(number)
	  printf("[%d, %ld] ",fileno,lineno);
	printf("%s \n",line);
	found++;	
	} //fin strstr
	} //end while getline
    }//end while fopen
  }//end else
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
