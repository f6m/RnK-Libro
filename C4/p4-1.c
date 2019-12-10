/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 4.1 */

/* funciom strrindex(s,t) que devuelve el indice de inicio de la cadena t mas a la izq. 
de la cadena s */


#include <stdio.h>
#include <string.h> 

int strindex(char s[], char t[]);
int strrindex(char s[], char t[]);

main(){
char s[' ']="hola que tal que paso";
char t[' ']="que";

printf("Indice de t en s mas a la izquierda= %i\n",strindex(s,t));
printf("Indice de t en s mas a la derecha= %i\n",strrindex(s,t));

return 0;
}

/* strindex : regresa el indice de t en s, -1 si no existe */
/* la posicion que entrega es la entrada de t mas a la izquierda */
int strindex(char s[], char t[])
{
int i,j,k;

for(i=0;s[i] != '\0';i++){
for(j=i,k=0;t[k]!='\0' && s[j]==t[k];j++,k++)
;
if(k>0 && t[k] == '\0')
return i;
}

return -1;
}

/* strrindex : regresa el indice de t en s, -1 si no existe */
/* la posicion que entrega es la entrada de t mas a la derecha */
int strrindex(char s[], char t[])
{
int i,j,k;

for(i=strlen(s)-1;i > 0;i--){
for(j=i,k=strlen(t)-1;k!=0 && s[j]==t[k];j--,k--)
;
if(k == 0)
return j;
}

return -1;
}
