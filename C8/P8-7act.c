/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 8.7 */
																				 
 /* La funcion malloc acepta un tamaño solicitado sin verificar
la posibilidad de que sea valido. Por su parte free cree que el bloque
que se pide liberar contiene un campo de tamaño correcto. 
Mejore estas rutinas para que se tomen mas molestias en la revision 
de errores.

para malloc
(1) revisamos si el parametro solicitado esta en el intervalo [0,SIZE_MAX]
si no regresamos error en la ferror.

para free:
(1) verificamos que el espacio apuntado no es vacio y esta en el intervalo [0,SIZe_MAX]
(2) verificamos que el apuntador enviado no sea NULL
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
 
/* Felipe Gayosso Martinez FGM*/
						
#include<stdio.h>
#include<string.h>
#include <stdint.h> //SIZE_MAX
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
if( ap == NULL){ //si el apuntador a eliminar es NULL anunciarlo en stderr y salir
fprintf(stderr, "Error %s \n", "apuntador nulo");
printf("ERR: Apuntador nulo \n");
return;
}
bp = (Header *)ap - 1; //le quitamos el + 1 del encabezado, nos posicionamos, se verifica que este en la direccion
if/bp->s.size == 0 || bp->s-size > MAX_SIZE) // no hay espacio o se sale del disponible
	{
	fprintf(stderr, "Error %s \n", "apuntador invalido");
	printf("ERR: Apuntador invalido \n");
	return;
}
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

  if (!(nu>=0 && nu <= SIZE_MAX)){ //nO esta en el rango permitido
	fprintf(stderr, "Error %s \n", "tamaño invalido");
	printf("Error %s \n", "tamaño invalido");
	return NULL; //como escribir en la salida estandar error 2	
	}

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

 printf("SIZE MAX : %lu\n",SIZE_MAX);
 
x = (int*)mallocc(sizeof(int)*10);
y = (struct rec *)mallocc(3*sizeof(struct rec));
 
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
}
