/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 2.3 */

/* El siguiente programa convierte una cadena que represente un numero  */
/* hexadecimal (prefijo 0x 0X) y lo convierte en un entero */
/* Obs.: la cadena de entrada la colocamos en un arreglo constante */
/* ctl + d es EOF */

#include <stdio.h> /* para usar printf */
#include <string.h> /* para usar strlen */

int htoi(char s[], int leng);

/* Caracteres para la cadena 0,...,9,a=10,b=11,c=12,d=13,e=14,f=15 */
/* num hex { '1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' } */
/* enum hex alfa;
 
 for(i=0;i<16;i++)
 {
   printf("%d es un caracter hex.\n",alfa+i);
 }
 */

main()
{
 int len,i;
 
 char line[]="0x2AF3";
 i=strlen(line);
 printf("La cadena hexadecimal es: %s\n",line);
 printf("Longitud:%i\n",i);
 printf("Su conversión a decimal es: %i\n",htoi(line,i));
 return 0;
 
}

// borra lo que encuentra entre comentarios 
int htoi(char s[],int leng)
{
 int i,j,n,x;
 /* Revisamos el prefijo 0x,0X */
 j=0;
 if (!(s[0] == '0' && (s[1] = 'x' || s[1] == 'X')))
 {
   printf("Advertencia: La cadena no tiene el prefijo hexadecimal!\n");
 }
 else {
   j = 2;
 }
 
 n=0; /* Este entero almacenara el valor decimal de la cadena */
 x=0; /* Este entero almacena el digito entontrado en la cadena */
 /* Revisamos que cada valor de entrada sea el adecuado */
 /* isxdigit() es otra opcion */
 for(i=j;i<leng;i++)
 {
   printf("Caracter inspeccionado: %c\n",s[i]);
   
   if (isdigit(s[i]) || s[i] == 'a' || s[i] == 'A' 
      || s[i] == 'b' || s[i] == 'B' || s[i] == 'c' || s[i] == 'C' 
      || s[i] == 'd' || s[i] == 'D' || s[i] == 'e' || s[i] == 'E'    
      || s[i] == 'f' || s[i] == 'F')
   {  
     if (isalpha(s[i])) {
       switch (tolower(s[i]))
       {
	 case 'a': x = 10;break;
	 case 'b': x = 11;break;
	 case 'c': x = 12;break;
	 case 'd': x = 13;break;
	 case 'e': x = 14;break;
	 case 'f': x = 15;break;
       }
     }
     if (isdigit(s[i])) {
       switch (s[i])
       {
	 case '0': x = 0;break;
	 case '1': x = 1;break;
	 case '2': x = 2;break;
	 case '3': x = 3;break;
	 case '4': x = 4;break;
	 case '5': x = 5;break;
	 case '6': x = 6;break;
	 case '7': x = 7;break;
	 case '8': x = 8;break;
	 case '9': x = 9;break;
       }
     }
     n = (n * 16) + x; 
     
     if(i==leng-1)
     { 
       printf("Cadena valida!\n");
     }
   }
   else
   {
     printf("Cadena no permitida, caracter %c no valido\n",s[i]);
   }
  } /* for */
  return n;
} /* checkopenclose function */





