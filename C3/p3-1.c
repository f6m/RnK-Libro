/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 3.1 */

/* Modificaciones al programa de busqueda binaria en un arreglo unidimensional */
/* Medimos el tiempo entre las dos versiones */
/* La busqueda binaria supone que el arreglo esta ordenado de forma creciente */
/* La comparacion de las dos funciones la realizamos con gprof */

#include <stdio.h>
#include <string.h>

int v[10]={1,2,10,20,35,66,74,82,95,135};

int binsearch1(int n, int x);
int binsearch2(int n, int x);

main() {
int x=10;
printf("Binary Search 1:%i\n",binsearch1(10,x));
printf("Binary Search 2:%i\n",binsearch2(10,x));
}

int binsearch1(int n, int x)
{
 int mid,low,up;
 extern v[10];

 low=0;
 up=n-1;
 while(low <= up){
 mid = (low+up)/2;
 if(x < v[mid])
	up = mid-1;
 else if(x > v[mid])
	low = mid+1;
 else return mid;
}
 return -1;	
}
int binsearch2(int n, int x)
{
 int mid,low,up;
 extern v[10];

 low=0;
 up=n-1;
 mid=(low+up)/2;
 while(low <= up && x != v[mid]){
 mid = (low+up)/2;
 if(x < v[mid])
	up = mid-1;
 else low = mid+1;
 }
 if(x == v[mid])
 return  mid;
 else
 return -1;	
}


