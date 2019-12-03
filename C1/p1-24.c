/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.24 */

/* El siguiente programa revisa los errores de no cerrar llaves, parentesis, corchetes */
/* comiilas y apostrofos en un programa en C*/
/* Obs.: No detecta errores por ejemplo que solo hay un ),],}. Hay que modificar usando una pila.
/* ctl + d es EOF */

#include <stdio.h>

#define MAX 10000
void checkopenclose(char s[], int leng);


main()
{
 int len, i;
 char line[MAX];
 char c;

 
 i=0;
 while((c = getchar()) != EOF){
    line[i++]=c;
 }
 printf("El texto es: %s\n",line);
 printf("Longitud:%i\n",i);
 checkopenclose(line,i);
 return 0;
 
}

// borra lo que encuentra entre comentarios 
void checkopenclose(char s[],int leng)
{
 int i,j;
 
 for(i=0;i<=leng;i++)
  {
   /* usar swich / case */
   
   switch (s[i]){
     
     case '(':
	      printf("Left parentesis index: %i\n",i);
	      j=i+1; /*primer caracter delante del '(' */   
	      while(s[j] != ')') 
	      {
		++j;
		if(s[j]==')')
		{
		  printf("Right parentesis index: %i\n",j);
		}
		if(j==leng)
		{
		  printf("Error right parentesis not found\n");
		  break;
		}
	      }             
     case '{': printf("Left key index: %i\n",i);
	       j=i+1; /*primer caracter delante del '(' */   
	       while(s[j] != '}') 
	      {
		++j;
		if(s[j]=='}')
		{
		  printf("Right key index: %i\n",j);
		}
		if(j==leng)
		{
		  printf("Error right key not found\n");
		  break;
		}
	      }
       
     case '[': printf("Left corchet index: %i\n",i);
	      j=i+1; /*primer caracter delante del '(' */   
	      while(s[j] != ']') 
	      {
		++j;
		if(s[j]==']')
		{
		  printf("Right corchet index: %i\n",j);
		}
		if(j==leng)
		{
		  printf("Error right corchet not found\n");
		  break;
		}
	      }
      case '\"':
	      printf("Left comilla index: %i\n",i);
	      j=i+1; /*primer caracter delante del '(' */   
	      while(s[j] != '\"') 
	      {
		++j;
		if(s[j]=='\"')
		{
		  printf("Right comilla index: %i\n",j);
		}
		if(j==leng)
		{
		  printf("Error right comilla not found\n");
		  break;
		}
	      }
     case '\'':
	      printf("Left apostrofe index: %i\n",i);
	      j=i+1; /*primer caracter delante del '(' */   
	      while(s[j] != '\'') 
	      {
		++j;
		if(s[j]== '\'')
		{
		  printf("Right apostrofe index: %i\n",j);
		}
		if(j==leng)
		{
		  printf("Error right apostrofe not found\n");
		  break;
		}
	      }
         
       
   } /* switch */

 } /* for */
} /* checkopenclose function */





