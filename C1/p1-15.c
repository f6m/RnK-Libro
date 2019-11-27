/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.15 */

/* Programa que imprime la tabla de conversiones Celsius-Fahrenheit para
celsius = 0,20,...,300; version punto flotante y con un encabezado y usando una funcion para la conversion */

#include<stdio.h>
float celciustofahr(float );
main(){
float fahr, celsius;
int lower,upper,step;
char *p = "TABLA DE CONVERSIONES DE CELSIUS A FAHRENHEIT";

lower = 0; /* Limite superior de la tabla de temperaturas */
upper = 300; /* Limite superior */
step = 20; /* tama¤o del incremento */

celsius = lower;
printf("%s\n",p);
while(celsius <= upper){
  fahr = celciustofahr(celsius) ;
	printf("%3.0f %6.1f\n",celsius,fahr);
	celsius = celsius + step;
	}
}

float celciustofahr(float c)
{
  return (9.0/5.0)*c + 32.0;
}
