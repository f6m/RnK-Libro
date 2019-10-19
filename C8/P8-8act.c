																				 
 /* Escriba una rutina bfree(p,n) que libere un bloque arbitrario
p de n caracteres, en la lista libre mantenida por malloc y free. Utilizando
bfree, un usuario puede agregar un arreglo estatico o externo a la lista libre 
en cualquier momento.

*/

 /* obs1: El espacio creado por mallocc no es continuo pero mantiene una lista ligada
para los espacios vacios*/
/*obs2: El espacio solicitado se asigna seleccionando el primer bloque de la lista de espacio libre
   donde cabe, despues considerando el remanente */
/*obs3: al liberar tambien se recorre la lista para enlazar el espacio liberado, freep apunta al inio de ese espacio*/
/* obs4: Align es propiamente el espacio asignado en terminos del tipo mas restrictivio: el long*/
/* Numero de programa (El lenguaje de programacion C, R&K, segunda edicion): 8.6 */
/* Pregunta como esta eso de que el linker junta las librerias y en los archivos encabezado solo esta la declaracion de las funciones */

/* POSIX es una norma escrita por la IEEE, que define una interfaz estándar del sistema operativo y el entorno, incluyendo un intérprete de comandos.​ */
 
/* Felipe Gayosso Martinez FGM, no del problemas 8.8 R&K 2da ed. */
/* revisar : https://github.com/andrewsuzuki/kr-solutions/blob/master/ch8/8-08/bfree.c */
						
#include<stdio.h>
#include<string.h>										
#include<unistd.h> //para sbrk()

typedef long Align; //para alineamiento al limite mayor

//porque union y no struct? Una union se aloja en un espacio contiguo de memoria, se utilizan sus elementos de forma unica
// una estructura en espacios separados, entonces se pueden usar sus elementos de forma simultanea
union header{
struct{
union header *ptr;
unsigned size;
} s;
Align x; //long
};

typedef union header Header; //typo los bloque se generaran en unidades multiplos de Header

//Todos los tipos de una union estan en el mismo bloque de memoria. 
static Header base; //header base, static porque solo podrian ser accesadas por funciones en el mismo programa, (opuesto a extern)
static Header *freep = NULL; //apuntador a header

#define NALLOC 1024

/*free: coloca el bloque de memoria apuntado por *ap como libre */
void freee(void *ap)
{
Header *bp,*p;
 bp = (Header *)ap - 1; //le quitamos el + 1 del encabezado, nos posicionamos, se verifica que este en la direccion
 //la condicion de for: p no esta antes de bp o p->s.ptr no esta despues de bp, si (bp<=p || bp>=p->s.ptr), 
 //Caso 1:
for(p=freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) //p se usa para recorrer iniciando en el apuntador a la lista de bloques vacios
	if(p >= p->s.ptr && (bp > p||bp<p->s.ptr))
	break;
//Caso 2:
if(bp + bp->s.size == p->s.ptr){ //se junta al nbr superior
  bp->s.size += p->s.ptr->s.size;//aumentas el tamaño de lo que quieres liberar
  bp->s.ptr = p->s.ptr->s.ptr;//enlazas ocupando ya el espacio
	}
else
bp->s.ptr = p->s.ptr;
if(p+p->s.size == bp){ //se junta al nbf inferior, si llegas a bp aumentandole a p su tamaño.
  p->s.size += bp->s.size; //incrementa el tamaño de free para alcanzar a bp.
  p->s.ptr = bp->s.ptr;//enlaza los apuntadores-
	}
else p->s.ptr = bp;
 freep = p; //ahora camria el apuntador freep al espacio vacio
}

/*bfree: coloca el bloque de memoria apuntado por *ap como libre
 n indica el numero de bloques alos que apunta ap; version modificando freee */
void bfreee1(void *ap, int n)
{
Header *bp,*p;
 bp = (Header *)ap - 1; //le quitamos el + 1 del encabezado, nos posicionamos al inicio del encabezado
unsigned nu = n / sizeof(Header); //tamaño de bloque, sizeof(Header)= #bytes, 
	if (nu <= 1){ //el tamaño de header excede el numero de bloques a liberar
	fprintf(stderr,"el tamaño de header excede el numero de bloques a liberar\n");
	printf("el tamaño de header excede el numero de bloques a liberar\n");
	return;
	}

if (freep == NULL) { //Si el apuntador al espacio libre es nullo.
        base.s.ptr = freep = &base;
        base.s.size = 0;
	}
bp->s.size = nu; //cambias el tamño del apuntador que vas a modificar.

 //la condicion de for: p no esta antes de bp o p->s.ptr no esta despues de bp, si (bp<=p || bp>=p->s.ptr)= !(p < bp < p->s.ptr)
 // en palabras: NO bp, como dir. mem., bp E [p,p->s.str] 
 //Caso 1: se comparan direccioines de memoria reservadas en el HEAP (como revisa su tamaño?)
for(p=freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) //p se usa para recorrer iniciando en el apuntador a la lista de bloques vacios
	if(p >= p->s.ptr && (bp > p||bp<p->s.ptr)) // (p->s.ptr<= p < bp) || (bp < p->s.ptr <= p)
	break; //si p E [p->s.ptr,bp) o p->s.ptr E (bp,p]
//OBS:El for no tiene llaves: se sale si for no cumple la condicion y bp E [p,p->s.str] 
//o se cumple el if y rompe el ciclo for con break: p E [p->s.ptr,bp) o p->s.ptr E (bp,p]
//Caso 2:
if(bp + bp->s.size == p->s.ptr){ //se junta al nbr superior
  bp->s.size += p->s.ptr->s.size;//aumentas libre, con el tamaño del apuntador bp mas 
  bp->s.ptr = p->s.ptr->s.ptr;//enlazas ocupando ya el espacio
	}
else bp->s.ptr = p->s.ptr; //no cabe en el blq delantero y aumentas el apuntador
if(p+p->s.size == bp){ //se junta al nbf inferior, si llegas a bp aumentandole a p su tamaño.
  p->s.size += bp->s.size; //incrementa el tamaño de free para alcanzar a bp.
  p->s.ptr = bp->s.ptr;//enlaza los apuntadores-
	}
else p->s.ptr = bp;
 freep = p; //ahora cambia el apuntador freep al espacio vacio modificado
}

/*bfree2: coloca el bloque de memoria apuntado por *ap como libre
 n indica el numero de bloques alos que apunta ap, version usanado free*/
void bfreee2(void *ap, int n)
{
Header *bp,*p;
 bp = (Header *)ap - 1; //le quitamos el + 1 del encabezado, nos posicionamos al inicio del encabezado
unsigned nu = n / sizeof(Header); //tamaño de bloque, sizeof(Header)= #bytes, 
	if (nu <= 1){ //el tamaño de header excede el numero de bloques a liberar
	  fprintf(stderr,"%s","el tamaño de header excede el numero de bloques a liberar\n");
	printf("el tamaño de header excede el numero de bloques a liberar\n");
	return;
	}

if (freep == NULL) { //Si el apuntador al espacio libre es nullo.
        base.s.ptr = freep = &base;
        base.s.size = 0;
	}
bp->s.size = nu; //cambias el tamño del apuntador que vas a modificar.

 freee((void *)(bp + 1)); 
}

/* morecore:  le solicita al sistema mas memoria */
static Header *morecore(unsigned nu)
{
char *cp;
// *sbrk(int); //borramos esta declaracion por los errores con declaraciones previas
Header *up;
 if(nu < NALLOC) //1024 = byte 
nu = NALLOC;
 cp = sbrk(nu * sizeof(Header)); //multiplos de union - Header, regresa un apuntador void*
 if(cp == (char *)-1) //tenia ASIGNACION Y NO IGUALDAD
  return NULL; //no se logro
 up = (Header *) cp; //convertimos cast Header
 up->s.size = nu; //asinamos el size
 freee((void*)(up+1)); //liberamos ?
return freep; //porque regresa freep? El apuntador al espacio liberado 
}

/* mallocc: Programa de proposito general para asignar memoria */
/* regresa un apuntador generico */
/* El espacio creado por mallocc no es continuo pero mantiene una lista ligada
para los espacios vacios*/

void *mallocc(unsigned nbytes)
{
Header *p, *prevp; //headed mallocc apuntadores
Header *morecore(unsigned); //declara la funcion dentro de otra funcion
unsigned nunits; //entero sin signo

nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1; //sizeof(Header) devuelve su tamaño en bytes
if((prevp = freep) == NULL){ //sin lista de espacios/bloque libres aun
base.s.ptr=freep=prevp=&base; //inicilizacion de prevp freep y base.s.ptr (apuntadores a base que ya cuenta con memoria)
base.s.size=0;
}
//inicia apuntando al espacio previo en su parte, prev=p hace que prev se establesca como previo
 for(p=prevp->s.ptr; ;prevp=p,p=p->s.ptr){ //no ha condicion en este for, solo ini y inc
	if(p->s.size >= nunits) { //hay espacio suficiente (en base inicialmente)
		if(p->s.size == nunits) //es exacto a las unidades requidas
		  prevp->s.ptr = p->s.ptr; //hace que el apuntador a la lista de espacio vacio apunte a prev, prev apunta al suguiente espacio, es prev por que apunta ->
	else { //p->s.size > nunits 
	p->s.size -= nunits; //reduces la cantidad actual con la que vas a tomar  
	p += p->s.size; //sumas el apuntador la cantiad indicada, esto es una direccion de mem., posicionas el apuntador al comienzo del bloque de memoria a usar
	p->s.size = nunits; //estableces el numero e bytes a usar 
    } //fin else
freep = prevp; //en freep comienza la lista de bloques libres
return (void *)(p+1); //regresa el apuntador al principio del bloque
} //fin if p->s.size < nunits no hay espacio suficiente o termino el proceso anterior
  if (p==freep)//
  if((p=morecore(nunits)) == NULL) //morecores 
	return NULL;
} //fin for
} //fin malloc


void *callocc1(unsigned nelem, unsigned size){
 Header *p, *prevp; //headed mallocc apuntadores
Header *morecore(unsigned); //declara la funcion dentro de otra funcion
unsigned nunits; //entero sin signo

 nunits = ((size*nelem) + sizeof(Header) - 1) / sizeof(Header) + 1; //Reservamos un bloque de size*nelem
if((prevp = freep) == NULL){ //sin lista de espacios/bloque libres aun
base.s.ptr=freep=prevp=&base; //inicilizacion de prevp freep y base.s.ptr (apuntadores a base que ya cuenta con memoria)
base.s.size=0;
}
//inicia apuntando al espacio previo en su parte, prev=p hace que prev se establesca como previo
 for(p=prevp->s.ptr; ;prevp=p,p=p->s.ptr){ //no ha condicion en este for, solo ini y inc
	if(p->s.size >= nunits) { //hay espacio suficiente (en base inicialmente)
		if(p->s.size == nunits) //es exacto a las unidades requidas
		  { 
		prevp->s.ptr = p->s.ptr; //hace que el apuntador a la lista de espacio vacio apunte a prev, prev apunta al suguiente espacio, es prev por que apunta ->
		p->x = 0; //inicializamos el espacio long long Aling x = 0		
		}
	else { //p->s.size > nunits : es mayor el espacio que se va a asignar.
	p->s.size -= nunits; //reduces el tamaño la cantidad actual con la que vas a tomar  
	p += p->s.size; //sumas la dir del apuntador la cantiad que queda, posicionandote al inicio de la memoria a ocupar, 
	p->s.size = nunits; //ahora estableces el numero e bytes a usar y al que estas apuntando como nunits
	p->x = 0; //inicializamos el espacio long long Aling x = 0
    } //fin else
freep = prevp; //en freep comienza la lista de bloques libres
return (void *)(p+1); //regresa el apuntador al principio del bloque
} //fin if p->s.size < nunits no hay espacio suficiente o termino el proceso anterior
  if (p==freep)//
  if((p=morecore(nunits)) == NULL) //morecores 
	return NULL;
} //fin for 
} //Fin calloc1

void *callocc2(unsigned nelem, unsigned size){
  void *p;
  int i;
  unsigned long int *q = (unsigned long int *)p;
  p=mallocc(nelem * size); //pero no inicializa la memoria a zero. malloc no inicializa
  for(i=0;i<=nelem-1;i++) //inicializacion
    q[i]=0;
  return p;
} //Fin calloc2

int main()
{
struct rec
	{
    		int i;
    		float PI;
    		char A;
	};
int *x;
struct rec *y;
 
x = (int*)mallocc(sizeof(int)*10);
y = (struct rec *)callocc1(3,sizeof(struct rec));

 
 if (x == NULL || y == NULL) {
  fprintf(stderr, "malloc fallo\n");
  return -1;
}

x[0]=0;
x[1]=1;
x[2]=2;

 printf("x[0]=%i\n",x[0]);
 printf("x[1]=%i\n",x[1]);
 printf("x[2]=%i\n",x[2]);

 y->i = 2;
 y->PI = 3.14;
 y->A = 'a';

 for(int i=0;i<3;i++){
 printf("y[%i]->i = %i\n",i,y[i].i);
 printf("y[%i]->PI = %f\n",i,y[i].PI);
 printf("y[%i]->A = %i\n",i,y[i].A);
}

 int V[16];
 
 for(int i=0;i<16;i++)
   {
     V[i]=i;
   printf("V[%d]=%i\n",i,V[i]);
   }
 
 bfreee1(V,sizeof(V));
 printf("V[%d]=%i\n",0,V[0]);

}
