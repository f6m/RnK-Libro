/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 5.10 */

/* Programa que simula la calculadora basica pasando argumentos a main, usando argc argv, y al cual se le ha agregado la operacion modulo, al cual se le agrego el reconocimiento de variables, utilizando a la variable double A para almacenar el ultimo calculo, 
 *ademas del operador = de asignacion, ejemplo A 2 = es A=2; Este programa esta basado en la rudimentaria calculadora
del capitulo 4 del mismo texto seccion 4.2*/

/* Si la llamada al programa usa la operacion de multiplicaicon esta operacion
necesita ser entrecomillada ejemplo: ./a.out ./a.out 4 4 3 '*' + */

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h> 

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
int getopl(char *s[],int);
void push(double);
double pop(void);
int pope(void);
double atof(char []);
int getch(void);
void ungetch(int);

int main(int argc, char *argv[]){
  
  int arg,type,variable,VAR[30];
  double op2,A=0;
  double B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z;
  double a,b,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,t,u,v,w,x,y,z;
  int ope2;
  char c[MAXOP],s[MAXOP];


  if(argc == 1) //solo esta el nombre del programa
    printf("Debes usar: expr patron\n");
  else {
    printf("El numero de argumentos es %i\n",argc);
    for(int i = 0; i<= argc-1 ;i++)
      printf( "argv[%i]:  %s\n",i,argv[i]);
    }
  
  arg=0;
  while(arg < argc-1){
    
    switch(type = getopl(argv,++arg)){
      printf("El caracter actal a analizar es %c\n",type);
    case NUMBER: 
      printf("Voy a meter a la pila %f\n",atof(argv[arg]));
      push(atof(argv[arg]));
      break;
    case '+':
      push(A = pop() + pop());
      break;
    case '*':
      push(A = pop()*pop());
      break;
    case '-':
      op2 = pop();
      push(A = pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0)
	push(A = pop()/op2);
      else
	printf("Error: Division por cero en la operacion division\n");
      break;
    case '%':
      ope2 = pope();
      if (ope2 != 0)
	push(A = pope() % ope2);
      else
	printf("Error: Division por cero en la operacion modulo\n");
      break;
    case '=':
      op2 = pop();
      variable = pope();printf("Se encontro = variable es %i y asignaremos %f a variable\n",variable,op2);
      switch(variable){
      case 'B':B = op2;push(B);VAR[1]=1;printf("Ahora variable vale %f\n",B);break;
      case 'C':C = op2;push(C);VAR[2]=1;printf("Ahora variable vale %f\n",C);break;
      case 'D':D = op2;push(D);VAR[3]=1;printf("Ahora variable vale %f\n",D);break;
      case 'E':E = op2;push(E);VAR[4]=1;printf("Ahora variable vale %f\n",E);break;
      case 'F':F = op2;push(F);VAR[5]=1;printf("Ahora variable vale %f\n",F);break;
      case 'G':G = op2;push(G);VAR[6]=1;printf("Ahora variable vale %f\n",G);break;
      case 'H':H = op2;push(H);VAR[7]=1;printf("Ahora variable vale %f\n",H);break;
      case 'I':I = op2;push(I);VAR[8]=1;printf("Ahora variable vale %f\n",I);break;
      case 'J':J = op2;push(J);VAR[9]=1;printf("Ahora variable vale %f\n",J);break;
      case 'K':K = op2;push(K);VAR[10]=1;printf("Ahora variable vale %f\n",K);break;
      case 'L':L = op2;push(L);VAR[11]=1;printf("Ahora variable vale %f\n",L);break;
      case 'M':M = op2;push(M);VAR[12]=1;printf("Ahora variable vale %f\n",M);break;
      case 'N':N = op2;push(N);VAR[13]=1;printf("Ahora variable vale %f\n",N);break;
      case 'O':O = op2;push(O);VAR[14]=1;printf("Ahora variable vale %f\n",O);break;
      case 'P':P = op2;push(P);VAR[15]=1;printf("Ahora variable vale %f\n",P);break;
      case 'Q':Q = op2;push(Q);VAR[16]=1;printf("Ahora variable vale %f\n",Q);break;
      case 'R':R = op2;push(R);VAR[17]=1;printf("Ahora variable vale %f\n",R);break;
      case 'S':S = op2;push(S);VAR[18]=1;printf("Ahora variable vale %f\n",S);break;
      case 'T':T = op2;push(T);VAR[19]=1;printf("Ahora variable vale %f\n",T);break;
      case 'U':U = op2;push(U);VAR[20]=1;printf("Ahora variable vale %f\n",U);break;
      case 'V':V = op2;push(V);VAR[21]=1;printf("Ahora variable vale %f\n",U);break;
      case 'W':W = op2;push(W);VAR[22]=1;printf("Ahora variable vale %f\n",W);break;
      case 'X':X = op2;push(X);VAR[23]=1;printf("Ahora variable vale %f\n",X);break;
      case 'Y':Y = op2;push(Y);VAR[24]=1;printf("Ahora variable vale %f\n",Y);break;
      case 'Z':Z = op2;push(Z);VAR[25]=1;printf("Ahora variable vale %f\n",Z);break;
      defalult: printf("Variable no es ninguna letra");break;
      }
      break;
    case '\n':
      printf("\t %.8g\n",pop());
      break;
    case 'A':
      push(A);
      break;
    case 'B':
      if(VAR[1] == 1) push(B);
      else push((double)'B');printf("Se encontro B\n");
      break;
    case 'C':
      if(VAR[2] == 1) push(C);
      else push((double)'C');printf("Se encontro C\n");
      break;
    case 'D':
      if(VAR[3] == 1) push(D);
      else push((double)'D');printf("Se encontro D\n");
      break;
    case 'E':
      if(VAR[4] == 1) push(E);
      else  push((double)'E');printf("Se encontro E\n");
      break;
    case 'F':
      if(VAR[5] == 1) push(F);
      else push((double)'F');printf("Se encontro F\n");
      break;
    case 'G':
      if(VAR[6] == 1) push(G);
      else  push((double)'G');printf("Se encontro G\n");
      break;
    case 'H':
      if(VAR[7] == 1) push(H);
      else  push((double)'H');printf("Se encontro H\n");
      break;
    case 'I':
      if(VAR[8] == 1) push(I);
      else  push((double)'I');printf("Se encontro I\n");
      break;
    case 'J':
      if(VAR[9] == 1) push(J);
      else  push((double)'J');printf("Se encontro J\n");
      break;
    case 'K':
      if(VAR[10] == 1) push(K);
      else   push((double)'K');printf("Se encontro K\n");
      break;
    case 'L':
      if(VAR[11] == 1) push(L);
      else   push((double)'L');printf("Se encontro L\n");
      break;
    case 'M':
      if(VAR[12] == 1) push(M);
      else  push((double)'M');printf("Se encontro M\n");
      break;
    case 'N':
      if(VAR[13] == 1) push(N);
      else  push((double)'N');printf("Se encontro N\n");
      break;
    case 'O':
      if(VAR[14] == 1) push(O);
      else push((double)'O');printf("Se encontro O\n");
      break;
    case 'P':
      if(VAR[15] == 1) push(P);
      else push((double)'P');printf("Se encontro P\n");
      break;
    case 'Q':
      if(VAR[16] == 1) push(Q);
      else push((double)'Q');printf("Se encontro Q\n");
      break;
    case 'R':
      if(VAR[17] == 1) push(R);
      else push((double)'R');printf("Se encontro R\n");
      break;
    case 'S':
      if(VAR[18] == 1) push(S);
      else  push((double)'S');printf("Se encontro S\n");
      break;
    case 'T':
      if(VAR[19] == 1) push(T);
      else  push((double)'T');printf("Se encontro T\n");
      break;
    case 'U':
      if(VAR[20] == 1) push(U);
      else  printf("Se encontro U\n");
      break;
    case 'V':
      if(VAR[21] == 1) push(V);
      else  push((double)'V');printf("Se encontro V\n");
      break;
    case 'W':
      if(VAR[22] == 1) push(W);
      else  push((double)'W');printf("Se encontro W\n");
      break;
    case 'X':
      if(VAR[23] == 1) push(X);
      else  push((double)'X');printf("Se encontro X\n");
      break;
    case 'Y':
      if(VAR[24] == 1) push(Y);
      else push((double)'Y');printf("Se encontro Y\n");
      break;
    case 'Z':
      if(VAR[25] == 1) push(Z);
      else  push((double)'Z');printf("Se encontro Z\n");
      break;
      
    default:
      if (type >= 'B' && type <= 'Z'){
	printf("Se encontro el caracter %s\n",c);
	printf("Error: Comando desconocido %s\n",c);}
      break;
    }
    printf("\t %.8g\n",A);
  }
  return 0;
}

  #define MAXVAL 100
  int sp = 0;
  double val[MAXVAL];


  /* Funcion push para introducir a la pila */
  void push(double f)
  {
    if (sp < MAXVAL)
      val[sp++] = f;
    else 
      printf("Error: pila llena, no puede efectuar push %g\n",f);
  }

  /* Funcion pop para regresar el valor superior de la pila */
  double pop(void){
    if(sp > 0)
      return val[--sp];
    else{
      printf("Error: pila vacia \n");
      return 0.0;
    }
  }


/* Version de pop que regresa un valor entero */ 
 int pope(void){
    if(sp > 0)
      return val[--sp];
    else{
      printf("Error: pila vacia \n");
      return 0;
    }
    }



  /* Funcion getop para obtener el siguiente operador u oparando numerico */
  int getop(char s[])
  {
    int i,c;

    while((s[0] = c = getch()) == ' ' || c == '\t')
      ;
    s[1]='\0';
    if (!isdigit(c) && c != '.')
      return c;
    i = 0;
    if (isdigit(c))
      while(isdigit(s[++i] = c = getch()))
	;
    if (c == '.')
      while(isdigit(s[++i] = c = getch()))
	;
    s[i] = '\0';
    if (c != EOF)
      ungetch(c);
    return NUMBER;
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
      	return c;
  }

  /* Funcion getopl para obtener el siguiente operador u oparando numerico en la linea de comandos usando argc y  argv*/
  int getopl(char *c[],int i)
  {
    int k,j=0;

    //    while(k = (*(c++))[i] != '\0')
      while((k = c[i][j]) != '\0')
      {
    if (!isdigit(k) && k != '.')
      return k;// No es un numero
    if (isdigit(k))
      while(isdigit(c[i][j++]))
	;//Reune la parte entera
    if (k == '.')
      while(isdigit(c[i][j++]))
	;//Reune la parte fraccionaria
    return NUMBER;
    if ((k >= 'A' && k <= 'Z') || (k >= 'a' && k <= 'z'))
      	return k;
    j++;
    }
  }

  #define BUFSIZE 100
  char buf[BUFSIZE];
  int bufp = 0;

  int getch(void)
  {
    return (bufp >0) ? buf[--bufp] : getchar();
  }

  void ungetch(int c)
  {
    if (bufp >= BUFSIZE)
      printf("ungetch: demasiados caracteres \n");
    else
      buf[bufp++] = c;
  }


/* La funcion atof que convierte una cadena a un numero flotante (double)*/
 
double atof(char s[]){
  double val, power;
  int i, sign;

  for(i=0;isspace(s[i]);i++)
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if(s[i] == '+' || s[i] == '-')
    i++;
  for(val = 0.0; isdigit(s[i]);i++)
    val = 10.0*val + (s[i] - '0');
  if(s[i] == '.')
    i++;
  for(power = 1.0;isdigit(s[i]);i++){
    val = 10.0*val + (s[i] - '0');
    power *= 10.0;
  }
  return sign*val/power;
}
