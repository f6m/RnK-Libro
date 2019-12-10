/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 4.2 */

/* extencion de la funcion atof, que convierte una cadena que expresa un numero de punto flotante
a su correspondiente valor decimal */
/* Esta extencion lee la expresiones del tipo 123.45e-6 */
/*Obs: s[i] - '0' proporciona el valor NUMERICO del caracter asociado a s[i], ya que '0','1' forman una secuencia creciente contigua.*/

#include <ctype.h>
#include <stdio.h>
#include <math.h>

double atof(char s[]){
double val, power,valexp;
int i, sign, expsign;

for(i=0;isspace(s[i]);i++) /* ignora los primeros espacios en blanco */
  ;
sign = (s[i] == '-')?-1:1; /* agrega signo a sign*/
if (s[i] == '+' || s[i]=='-') /*incrementa para encontrar el primer caracter*/
  i++;
for(val = 0.0;isdigit(s[i]);i++)
  val=10.0*val + (s[i] - '0'); /* val = s[i] - '0' = 1, val = 10 + 2= 12 */
if(s[i] == '.')
  i++;
for(power = 1.0;isdigit(s[i]);i++){
  val = 10.0 * val + (s[i] - '0'); /* val = 12*10 + 2 = 122, val = 1220 + 3 = 1223 *
  power *= 10.0; /* 10, 100,... */
/* val realiza la expansion en potencias de 10 requerida para saber el numero*/
}
if(s[i] == 'e' || s[i] == 'E')
  i++; /*Si encontramos el signo que define la notacion e o E incrementamos el indice, para encontrar el valor b hay que elevar 10^b*/
expsign = (s[i] == '-')?-1:1; /* agrega signo a expsign*/
if(s[i] == '+' || s[i] == '-')
 i++; /*incrementamos para encontrar el valor de b*/
for(valexp = 0.0;isdigit(s[i]);i++)
  valexp=10.0*valexp + (s[i] - '0'); /* valexp realiza la expansion en potencias de 10 requerida para saber el numero*/
 
 printf("calexp = %f \n",valexp); 
  
return sign*val/power*(pow(10,(expsign)*valexp)); /* 1223 / 100 */

}

main(){
char s[' ']="-12.23e-12";

printf("Cadena %s\n",s);
printf("Double %10.12f\n",atof(s));

}
