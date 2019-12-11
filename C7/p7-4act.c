/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 7.4 */

/* El siguiente programa crea una versio miniscanf minimalista de
scanf similar al programa 7-3 que se hizo una version miniprintf (version simple de printf)
introducida en el libro */

/* Las acciones a implementar son:
(1) Lectura de caracteres octales y hexadecimales banderas o/h, apuntadores void *
(2) Lectura de Notacion cientifica banderas E/e 
(3) maximo numero de caracteres por cadena printf("%.*s",max,s) 
(4) presicion -10.14 para cadenas y para enteros y reales*/
/* obs1: Se puede usar el reconocimieto previo del formato que comienza con %y termina con el caracter
   e f s c etc */ 

#include <stdio.h>
#include <string.h>
#include <stdarg.h> //Contiene macrodefiniciones que definen como avanzar en una lista de argumentos
#include <string.h>

void miniscanf(char *fmt, ...) //los tres puntos indican que puede haber varios campos
{
va_list ap; //apunta a cada argumento sin nombre y en orden
char *p, *sval;
int *ival;
double dval;
void *vval;
char minfmt[20]; //para almacenar el fmt actual
int num,i;
 
va_start(ap,fmt); //hace que ap apunte al primer caracter de la cadena del formato para scanf
for(p = fmt; *p; p++){
if(*p != '%')
{
putchar(*p);
continue;
}//fin-if
 minfmt[0]='%';
 for(i=1;isalnum(*p++);i++) //guardamos el primer formato
   minfmt[i]=*p;
 minfmt[i++]=*p;
 minfmt[i]='\0';

switch(*p){
case 'd':
	ival = va_arg(ap, int *);
	scanf(minfmt,ival);break;
case 'i':ival = va_arg(ap, int *);
	scanf(minfmt,ival);break;
case 'o':ival = va_arg(ap, int *);
	scanf(minfmt,ival);break; //numero octal sin signo
case 'x':ival = va_arg(ap, int *);
	scanf(minfmt,ival);break; //numero hex sin signo
case 'f':dval = va_arg(ap, double);
	scanf(minfmt,&dval);break;
case 'e':dval = va_arg(ap, double);
	scanf("%e",&dval);break;
case 'p':vval = va_arg(ap, void *);
	scanf("%p",&vval);break;
case 's':sval = va_arg(ap, char *);
	scanf(minfmt,sval);break;
default: putchar(*p);break;
} //fin-switch

} //fin-for
 va_end(ap);
} //fin-mini

main()
{
  int len, num;
  int val=12413;
  double max=2.1416;
  char line[100]="hola";
  char *q=line;
  void *p=line;
  miniscanf("Int d: %d \t Int i: %i \t Cadena: %s \n",&len, &num,line);
  printf("Int d: %d \t Int i: %i \t Cadena: %s \n",len,num,line);
  //miniprintf("Int i: %i \t Int oct: %o \t Int hex: %x \n",len,len,len);
  //miniprintf("double notacion cientifica: %e \t void *: %p \t Int hex: %x \n",max,p,len);
  //miniprintf("%.*s\n",q);
  //printf("%.*d \n",4,val);

  return 0;
}
