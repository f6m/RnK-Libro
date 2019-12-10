/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.9 */

/* Programa que implementa el uso de arreglos multidimensionales, en este caso 
 * arreglos de dos dimensiones, lo ejemplifica con dos funciones day_of_year, que
 * convierte el numero de mes mas el numero de su dia en en dia global del año, y
 * month_day que convierte el dia del año en el mes y dia. 
 * Hay que agregar la deteccion de errores de entrada para ambas funciones
*/
/* Esta vez vamos a reescribir month_day y day_of_year usando apuntadores */


#include <stdio.h>
#include <string.h>

/* static arreglo bidimensional que almacena los vectores con entradas para los dias de los
 * meses en años bisiestos y no bisicestos */

static char daytab[2][13] = {
  {0,31,28,31,30,31,30,31,31,30,31,30,31},
  {0,31,29,31,30,31,30,31,31,30,31,30,31},
};

int month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;
  
  if((year < 0)){ 
  printf("Año invalido\n");
  return 0;
  }
  if(yearday < 0 || yearday > 366){
  printf("Numero de dia inválido\n");
  return 0;
  }
  
  /* esta variable decide si es año biciesto o no*/
  leap = (year%4 == 0) && (year%100 != 0) || (year%400 == 0);
  
  /* con la variable i recorremos dias de cada mes del año */
  for(i=1;yearday > *(*(daytab+leap)+i); i++) /* siempre que el dia del año sea mayor al numero de dia del mes */
    yearday -= *(*(daytab+leap)+i); /* reduces el año de entrada con los dias de los meses empezando por enero,.. */
  *pmonth = i; /*asignamos al apuntador pmonth el valor de la variable automatica i*/
  *pday = yearday; /* asignamos el resultado de yearday al apuntador *pday */
}

int day_of_year(int year, int month, int day)
{
   int i, leap;
  
  if((year < 0)){ 
     printf("Año invalido\n");
     return 0;
  }
  if(month < 1 || month > 12){
    printf("Numero de mes inválido\n");
  return 0;
  }
  /* esta variable decide si es año biciesto o no*/
  leap = (year%4 == 0) && (year%100 != 0) || (year%400 == 0);
  
  /* con la variable i recorremos dias de cada mes del año */
  for(i=1;i < month; i++) /* siempre que el dia del año sea mayor al numero de dia del mes */
    day += *(*(daytab+leap)+i); /* reduces el año de entrada con los dias de los meses empezando por enero,.. */
  return day; /* devolvemos day */ 
}


main(){
  int y=1988;
  int d=60;
  int m=1;
  
  printf("El dia %i del año %i\n",d,y);
  month_day(y,d,&m,&d);
  printf("Es el dia %i del mes %i\n",d,m);
  
  y=1988;
  d=20;
  m=10;
  
  printf("El dia %i del mes %i del año %i\n",d,m,y);
  printf("Es el dia %i del año %i\n",day_of_year(y,m,d),y);
  
} 

