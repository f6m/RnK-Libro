/* El lenguaje de programacion C, R&K, (Prentic Hall, 2da. edicion, 1991) */
/* # 1.3 */

/* Programa que imprime la tabla de conversiones Fahrenheit-Celsius para
fahr = 0,20,...,300; version con punto flotante y con un encabezado */

#include<stdio.h>

main(){
float fahr, celsius;
int lower,upper,step;
char *p = "TABLA DE CONVERSIONES DE FAHRENHEIT A CELSIUS ";

lower = 0; /* Limite superior de la tabla de temperaturas */
upper = 300; /* Limite superior */
step = 20; /* tama\~no del incremento */

fahr = lower;
printf("%s\n",p);
while(fahr <= upper){
	celsius= (9.0/5.0)*(fahr + 32.0);
	printf("%3.0f %6.1f\n",fahr,celsius);
	fahr = fahr + step;
	}
}
