/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 3.3 */

/* Programa que expande cadenas como a-z a abcd...xyz */

#include <stdio.h>
#include <string.h>

void expand(char * s1, char * s2);

int main(void) {
    char *s[] = { "a-z-", "z-a-", "-1-6-",
                  "a-ee-a", "a-R-L", "1-9-1",
                  "5-5", NULL };
    char result[100];
    int i = 0;
    
    while ( s[i] ) {
        
        /*  Expande e imprime la siguiente cadena del array s[]  */
        
        expand(result, s[i]);
        printf("Cadena sin expander: %s\n", s[i]);
        printf("Cadena expandida   : %s\n", result);
        ++i;
    }
    
    return 0;
}


/*  Copia las cadenas s2 a s1, expandiendo
    los rangos 'a-z' y '8-3'     */

void expand(char * s1, char * s2) {
    static char upper_alph[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static char lower_alph[27] = "abcdefghijklmnopqrstuvwxyz";
    static char digits[11]     = "0123456789";
    
    char * start, * end, * p;
    int i = 0;
    int j = 0;
    
    
    /*  Busca en los caracteres de s2  */
    
    while ( s2[i] ) {
        switch( s2[i] ) {
        case '-':
            if ( i == 0 || s2[i+1] == '\0' ) {
                
                              
                s1[j++] = '-';
                ++i;
                break;
            }
            else {
                
                               
                if ( (start = strchr(upper_alph, s2[i-1])) &&
                     (end   = strchr(upper_alph, s2[i+1])) )
                    ;
                else if ( (start = strchr(lower_alph, s2[i-1])) &&
                          (end   = strchr(lower_alph, s2[i+1])) )
                    ;
                else if ( (start = strchr(digits, s2[i-1])) &&
                          (end   = strchr(digits, s2[i+1])) )
                    ;
                else {
                    
                                        
                    fprintf(stderr, "EX3_3: Mismatched operands '%c-%c'\n",
                            s2[i-1], s2[i+1]);
                    s1[j++] = s2[i-1];
                    s1[j++] = s2[i++];
                    break;
                }
                
                
                /*  Expande el rango */
                
                p = start;
                while ( p != end ) {
                    s1[j++] = *p;
                    if ( end > start )
                        ++p;
                    else
                        --p;
                }
                s1[j++] = *p;
                i += 2;
            }
            break;
            
        default:
            if ( s2[i+1] == '-' && s2[i+2] != '\0' ) {
                
                ++i;
            }
            else {
                                         
                s1[j++] = s2[i++];
            }
            break;
        }
    }
    s1[j] = s2[i]; 
}


