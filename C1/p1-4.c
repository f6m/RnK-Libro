/* El lenguaje de programacion C, R&K, (Prentic Hall, 2da. edicion, 1991) */
/* # 1.4 */

/* Programa que imprime la tabla de conversiones Celsius-Fahrenheit para
celsius = 0,20,...,300; version punto flotante y con un encabezado */

#include<stdio.h>

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
	fahr = (9.0/5.0)*celsius + 32.0;
	printf("%3.0f %6.1f\n",celsius,fahr);
	celsius = celsius + step;
	}
}
