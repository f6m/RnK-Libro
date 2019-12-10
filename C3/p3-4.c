/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 3.4 */

/* En una representacion de enteros complemento a 2, muestra que itoa no maneja
el numero negativo mas grande, esto es, el valor de n igual a -2^(tamaño palabra - 1) */
/* Explicar por que, modifique itoa para imprimir el valor correctamente, sin importar
 * la maquina donde lo ejecute */

/* El complemento a 2 de un numero binario n de N bits lo obtienes restandole a 2^N=10000..0
 * dicho numero.
 * 110 -> 1000 - 110 = 010
 * O tomando intecambiando 0<->1 y sumando 1, 110<->001 + 1 = 010
 *Entonces, el entero mayor lo determina el tamaño de la palabra es el numero de bits N,
 * Observacion: 2^N se representa como 10000...000 con 1 + N 0's y tiene un espacio de N+1 bits,
 * por lo tanto no es represntable con N bits, luego 2^(N-1) ocupa N bits si es representable.
 * con una palabra de N bits.
 * Como en el complemento a 2 necesitamos tener 2^N, entonces el numero positivo mayor puede se 2^(N-1)-1
 * que es 1111---111 N 1's.
 * para enteros negativos...el bit mas a la isquierda representa su signo, con un 1.
 * y en el sistema de complemento a dos representamos el numero negativo como 
 * su complemento a dos C2(existe tambien la notacion bit magnitud y complemento a 1 C1)
 * Entonces 7 = -3 = 111, C2(111)= 000 + 1 = 001 = 1
 *          6 = -2 = 110, C2(110)= 001 + 1 = 010 = 2
 * 	    5 = -1 = 101, C2(101)= 010 + 1 = 011 = 3
 *           = -128 = 110000000 C2(110000000) = 001111111 + 1 =10000000 = 128
 *          11111111, C2(1111 1111) = 0000 0001 = -1 (el C2 se interpreta como el negativo
 *  para numeros que tienen un bit 1 mas a la isquierda)
 *          1000...000 (1+(N-1) 0's) C2(1000...000) = 0111...1111 
    Entonces, como N bits reparten N/2 numeros positivos (bit mas a la izq. 0) y N/2
    numeros negativos (bit mas a la izq. 1) el numero negativo mas grande expresado 
    en C2 es 100..0000 (1 + N-1 0's) pues C2(100..0000) = 0111..111 + 1 = 1000..00 = 2^(N-1)
    ya que los indices dela potencias de 2 son 2^0,2^1,...2^(N-1) */



#include <stdio.h>
#include <string.h>

void itoa1(int n, char s[]);
void itoa2(int n, char s[]);
void reverse(char s[]);

main(void) {
    int n = -12;
    char s[10]="hola";

    printf("Entero :%i\n",n);
    itoa2(n,s);
    printf("Cadena :%s\n",s);
      
    return 0;


}

void itoa1(int n, char s[]){
  int i,j,sign;
  
  if((sign = n) < 0) /* entero negativo */
    n = -n; /* Al volver el numero negativo en positivo tenemos como maximo un numero
	     2^(N-1) - 1, por lo tanto no alcanza la cota 2^(N-1) para negativos en C2*/
  i=0;
  do{
    s[i++]=n%10 + '0';
  }while((n/=10)>0);
  if(sign < 0) /* vamos a modificar aqui con if((sign = n) < 0) y borrar lo anterior */
    s[i++]='-';
    s[i]='\0';
}

void reverse(char s[]){
int c,i,j;
for(i=0,j=strlen(s)-1;i<j;i++,j--){
c=s[i];
s[i]=s[j];
s[j]=c;
}
}

void itoa2(int n, char s[]){
  int i,j,sign;
  sign = n;
  if(n < 0) /* entero negativo */
   { 
     i=0;
      do{
	s[i++]=(-n)%(10) + '0';
	}while((n/=10)<0);
   }
  else
  {
     i=0;
     do{
       s[i++]=n%10 + '0';
       }while((n/=10)>0);
  }
  if(sign < 0) 
    s[i++]='-';
 
  s[i]='\0';
      reverse(s);

}
