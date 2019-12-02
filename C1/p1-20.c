/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 1.20 */

/* Programa detab que reemplaza tabuladores de la entrada con el numero apropiado de blancos para espaciar hasta el siguiente paro de tabulacion. Considere un conjunto fijo de paros de tabulacion, digamos cada n columnas. 
 ¿ Debe ser n una variable o un parametro simbolico? Ambos casos pueden dar pie a un programa
 Utilizamos Ctrl + D para indicar el EOF
 compilamos con gcc -o p p1-20.c -lm */

#include <stdio.h>
#include <string.h>

void copy(char to[], char from[]);
//void blanksj(char to[], int m);

main(){
  int i,j,k,r,c;
  char s[' '],sb[' '],tmp[' '];
  
  i=0;
    while((c = getchar()) != EOF)
    {
      s[i]=c;
      ++i;
       }
    
    printf("\n %s :Cadena guardada \n",s);
    printf("Longitud: %d\n",strlen(s));
    copy(sb,s);
    for(j=0;j <strlen(s);j++)
    {
           
      if(s[j]=='\t')
      {      
	r=0;
	for(k=j;k < strlen(s);k++)
	{
	  tmp[r]=s[k+1];
	  r++;
	}

      printf("Segunda parte de cadena: %s\n",tmp);
      sb[j]='\%';
      sb[j+1]='\%';
      sb[j+2]='\%';
      sb[j+3]='\%';
      sb[j+4]='\%';
      sb[j+5]='\%';
      sb[j+6]='\0';
      printf("Primera parte de cadena: %s\n",sb);
      strcat(sb,tmp);
      printf("\n %s :Cadena con caracteres blancos y longitud %d\n",sb,strlen(sb));
      copy(s,sb);
      }
    }
      printf("\n %s :Cadena con final con 6 caracteres blancos por un tabulador \n",sb);
      printf("Longitud: %d",strlen(sb));
      
}
 
 
// Inserta los blancos necesarios para un tabulador

//void blanksj(char to[], int m)
//{
  //char tmp[];
  //for
//}
    // copy: copia 'from' en 'to'; supone que to es suficientemente grande

void copy(char to[], char from[])
{
  int i;

  i=0;
  while((to[i] = from[i]) != '\0')
	++i;
}

