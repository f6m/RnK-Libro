/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.21 */

/* Programa entab que reemplaza caracteres formados por espacios en blanco por su correspondientes tabuladores y 
 espacios en blanco hasta el siguiente paro de tabulacion. Considere los paros de tabulacion de la misma forma que en detab
Cuando un simple tab o blanco fuese suficiente para alcanzar un paro de tabulacion ¿a cual se le debe dar preferencia?
 Utilizamos Ctrl + D para indicar el EOF
 compilamos con gcc -o p p1-20.c -lm */

#include <stdio.h>
#include <string.h>

void copy(char to[], char from[]);
void blanksij(char to[], int in,int fi);

main(){
  int i,j,k,m,r,c;
  char s[' ']="i          j          k",sb[' '],tmp[' '];
  
  //i=0;
   // while((s[i] = getchar()) != EOF)
    //{
     // i++;
      // }
    
    printf("Cadena guardada:%s\n",s);
    copy(sb,s);
    
   for(j=0;j<strlen(sb);j++)
    {
      printf("La cadena actual es:%s y su longitud: %d\n",sb,strlen(sb));
      printf("para j = %d tenemos s[%d]= %c\n",j,j,s[j]);
      if(sb[j]==' ')
      {  
	m=0;     
	for(i=j;sb[i]==' ';i++)
	{
	++m;
	}
	if(m<6){
	  printf("Hay menos de seis blancos en este bloque---> lo dejamos con blancos\n");
	}
	printf("El numero de espacios en blanco en este bloque es: %d con indices (%d,%d) \n",m,j,j+m);
	
	//r=0;
	//for(k=m;k < strlen(s);k++)
	//{
	 // tmp[r]=s[k+1];
	  //r++;
	//}
	//printf("Segunda parte de la cadena %s \n",tmp);
      
      }
      
      if(m>=6)
	{
	printf("Hay almenos seis blancos\n");
        blanksij(sb,j,j+m);
        //printf("nos moveremos a la posicion %d\n",j);
	}
	
    }
      printf("\n %s :Cadena con final con cada 6 caracteres blancos replazados por un tabulador \n",sb);
      //printf("Longitud: %d",strlen(sb));
      
}
 
 
// Inserta los blancos y tabuladores necesarios para cubrir
// un bloque de blancos a partir de dos indices

void blanksij(char to[], int in, int fi)
{
  int n,i,j,b,r=0;
  char tmp[' '];
  
  n=(fi-in)/6;
  b=(fi-in)%6;
  printf("el numero de tabs a insertar es %d y sobran %d blancos \n",n,b);
  
   for(j=fi;j<=strlen(to);j++)
  {
    tmp[r++]=to[j];
  }
  
  printf("la cadena despues del bloque de blancos es %s\n",tmp);
 
  for(i=0;i<n;i++)
  {
    to[in+i]='*';
  }
  
  to[in+n+b]='\0'; //agregamos el fin de archivo
  printf("La primera parte de la cadena es %s\n",to);
  strcat(to,tmp);
  printf("la cadena con tabuladores es %s\n",to);
}
 
// copy: copia 'from' en 'to'; supone que to es suficientemente grande

void copy(char to[], char from[])
{
  int i;

  i=0;
  while((to[i] = from[i]) != '\0')
	++i;
}

