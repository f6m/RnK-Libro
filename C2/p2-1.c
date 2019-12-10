/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.1 */

/* Programa que muestra los tamaños de los distintos tipos de datos asi como sus respectivos rangos usando dos alternativas, el calculo directo sobre el numero de bits y el archivo limits.h */

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

void BytesDatos(void);


main(){
  BytesDatos();
}


void BytesDatos(void)
{

struct {
signed int a;
unsigned int d;
signed char i;
unsigned char h;
long f;
short g;
unsigned long e;
unsigned short j;
} tam;

 printf("El numero de bytes para los enteros con signo es %i, rango: %i - %i\n", sizeof(tam.a),(int) -pow(2,8*sizeof(tam.a)-1),(int) pow(2,8*sizeof(tam.a)-1));
 printf("El numero de bytes para los enteros sin signo es %i, rango: 0 - %i\n", sizeof(tam.d),(int) pow(2,8*sizeof(tam.d))-1);
 printf("El numero de bytes para los enteros largos con signo es %i, rango: %i - %i\n", sizeof(tam.f),(int) -pow(2,8*sizeof(tam.f)-1),(int) pow(2,8*sizeof(tam.f)-1));
 printf("El numero de bytes para los enteros largos sin signo es %i, rango: 0 - %i\n", sizeof(tam.e),(int) pow(2,8*sizeof(tam.e))-1);
 printf("El numero de bytes para los enteros cortos con signo es %i, rango: %i - %i\n", sizeof(tam.g),(int) -pow(2,8*sizeof(tam.g)-1),(int) pow(2,8*sizeof(tam.g)-1));
 printf("El numero de bytes para los enteros cortos sin signo es %i, rango: 0 - %i\n", sizeof(tam.j),(int) pow(2,8*sizeof(tam.j))-1);
 printf("El numero de bytes para los caracteres con signo es %i, rango: %i - %i\n", sizeof(tam.i),(int) -pow(2,8*sizeof(tam.i)-1),(int) pow(2,8*sizeof(tam.i)-1));
 printf("El numero de bytes para los caracteres sin signo es %i, rango: 0 - %i\n", sizeof(tam.h),(int) pow(2,8*sizeof(tam.h))-1);
 printf("El numero de bytes para la estructura que los define es %d\n", sizeof(tam));

 /* Calculamos estos valores usando las constantes definidas en el header limits.h */

 printf("Usando las constantes definidas en limits.h\n");
 printf("El numero de bytes para los enteros con signo es %i, rango: %i - %i\n", sizeof(tam.a),INT_MIN,INT_MAX);
 printf("El numero de bytes para los enteros sin signo es %i, rango: %i - %iL\n", sizeof(tam.d),0,UINT_MAX);
 printf("El numero de bytes para los enteros largos con signo es %i, rango: %i - %i\n", sizeof(tam.e),LONG_MIN,LONG_MAX);
 printf("El numero de bytes para los enteros cortos con signo es %i, rango: %i - %i\n", sizeof(tam.g),SHRT_MIN,SHRT_MAX);
 printf("El numero de bytes para los caracteres con signo es %i, rango: %i - %i\n", CHAR_BIT,SCHAR_MIN,SCHAR_MAX);
 printf("El numero de bytes para los caracteres sin signo es %i, rango: %i - %i\n", CHAR_BIT,0,UCHAR_MAX);

}
