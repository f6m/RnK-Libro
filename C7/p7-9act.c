

/* Se puede escribir funciones como isupper/islower para ahorrar
ESPACIO O TIEMPO. Explore ambas posibilidades

/* Un conjunto de archivos tomados con los parametros argc/argv e imprime cada uno por pantallas */
/* Numero de programa (El lenguaje de programacion C, R&K, segunda edicion): 7.9 */ 
/* Felipe Gayosso Martinez */


/* Funcion getline que obtiene un linea la almacena en s y tiene longitud maxima lim */
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define LINEPAGE 40 //40 lineas por pagina en cada archivo



/* Decide si una letra es mayuscula o no: Buen tiempo */

int isupperr1(int c)
{
  if(c >= 'A' && c <= 'Z')
    return 1;
	else return 0;
} 

int isupperr2(int c)
{
  (c >= 'A' && c <= 'Z')? return 1: return 0;
} 

//find: imprime lineas que coinciden con el patron del 1er. argumento */
/* Imprime archivos en stdout(panatalla), contandolos e indicando su inicio/fin */
main(int argc, char *argv[]){
 char c='Z';
if(isupperr2(c))//hay archivos
   printf("%c es mayuscula \n",c);
	else printf("%c no es mayuscula \n",c);
} //end main

