/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 8.2 */

/*
programa que implementa una version de getc y fopen usando CAMPOS en lugar
de los operadores a nivel de bits : &,|

obs1: Para usar evitar la redefinicion usamos fopenn, FILEE,etc.
obs2: ((fp->flag & (_READ | _WRITE)) == 0)
((fp->flag & _READ  | fp->flag & _WRITE) == 0)
es distinto de cero si AMBOS son DISTINTOS de cero, ES DECIR SI fp->flag!=0

obs3: Par usar campos declaramos la variable flag como una estructura.

obs4: fp->flag->_WRITE es fp->flag._WRITE, el lado izquierdo de -> debe ser apuntador

obs5:  ((fp->flag & (_READ | _EOF | _ERR)) != _READ) =
      ((fp->flag & _READ | fp->flag & _EOF | fp->flag & _ERR) != _READ)
es equivalente a 
      ((fp->flag._READ == 0) || (fp->flag._EOF == 1) || (fp->flag._ERR == 1))
obs6: fp->flag |= _EOF es equivalente a fp->flag = fp->flag | _EOF que en terminos de campos
es fp->flag._EOF=1

 */

/*
Una var static en funciones guarda su valor entre invocaciones
Una var static global o una funcion es vista solo en el archivo que es declarado */

/*
obs1: ¿Cuale es el tamaño max de un archivo que se puede leer.? BUFSIZ
obs2: Es necesario usar el buffer buf[BUFSIZ] ? */

#include <stdio.h> //para BUFSIZ
#include <fcntl.h> //para open / creat
#include <syscall.h>
#include <stdlib.h> //para exit
//#include <unistd.h>

#define NULLL 0 //NULL POINTER
#define EOFF -1 //fin de archivo
#define BUFSIZEE 1024 //UN BYTE
#define OPEN_MAX 20 // MAX NUM DE ARCHIVO ABIERTOS A LA VEZ

//Estructura flag
typedef struct flagg{
  short _READ;
  short _WRITE;
  short _UNBUF;
  short _EOF;
  short _ERR;
} FLAGG;

//Estructura archivo
typedef struct _iobuf{
int cnt; // caracteres que quedan
char *ptr; //posicion del siguiente caracter 
char *base; // localizacion del bufer
FLAGG flag; //banderas de acceso al archivo
int fd; //descriptor del archivo
} FILEE;

//extern FILEE _iob[OPEN_MAX]; //ARREGLO  de 20 estructuras archivo
//E/S/ERR

#define stdin (&_iob[0]) // envia la direccion de _ioib[0]
#define stdout (&_iob[1]) // envia la direccion de _ioib[0]
#define stderr (&_iob[2]) //para que el & es algun error? es una operacion a nivel de bits and

enum _flags{
  _READ = 01, //octal 01
  _WRITE = 02, //octal 02 binario 10 
  _UNBUF = 04, //octal 04 binario 100
  _EOF = 010, //octal 010 binario 1010
  _ERR = 020 //octal 020 binario 10010
};

int _fillbuf(FILEE *); //para llenar el buf?
int _flushbuf(int , FILEE *); //PARA VACIAR EL BUF?
FILEE *fopenn(char *, char *); //Definicion de fopenn

#define feof(p)   (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0) ? (unsigned char) *(p)->ptr++ : _filbuf(p))
#define putc(x,p) (--(p)->cnt >= 0) ? (unsigned char) *(p)->ptr++ = (x) : _flushbuf((x),p))
#define getchar() getc(stdin)
#define putchar(x) putc((x),stdout)

#define PERMS 0666 //lectura y escritura para propietario, grupo y otros

/* FILEE _iob[OPEN_MAX]={
  {0,(char *) 0, (char *) 0, _READ,0},
  {0,(char *) 0, (char *) 0, _WRITE,1},
  {0,(char *) 0, (char *) 0, _WRITE | _UNBUF,2},
};*/

//Inicializacion con la estructura
FILEE _iob[OPEN_MAX]={
  {0,(char *) 0, (char *) 0, {1,0,0,0,0},0},
  {0,(char *) 0, (char *) 0, {0,1,0,0,0},1},
  {0,(char *) 0, (char *) 0, {0,1,1,0,0},2},
};

// Main : 
main(int argc, char *argv[])
{
char *prog = argv[0]; //nombre del programa
FILEE *fp;
 short val;
 val = _READ | _WRITE; //01 | 02
printf("(_READ | _WRITE)= %d\n",val);
if(argc == 2){ //Si no se invoca con prog file1 file2 
	if((fp = fopenn(argv[1],"r")) != NULLL){ //el fopen que se implemento 
	printf("Archivo abierto con exito\n");
	val = _fillbuf(fp);
	printf("Buffer preparado con %d bytes \n",val);
	}
	else { 
	error("cat: %s nos se puede abrir %s\n",prog,argv[1]);
	exit(1);
	}
}
exit(0);
}

/* fopen : abre un archivo, regresa un apuntado de archivo */
FILEE *fopenn(char *name, char *mode) //
{
int fd; //para el descriptor
FILEE *fp; //archivo estructura FILE

if (*mode != 'r' && *mode != 'w' && *mode != 'a') //El modo para abrir el archivo
return NULLL; //fin regresa null si no es un modo permitido

for(fp=_iob; fp < _iob + OPEN_MAX; fp++) //se recorre el arreglo de estruct file hasta los 40 archivos permitidos
  if ((fp->flag._READ==0) && ((fp->flag._WRITE) == 0)) //_READ = 01, _WRITE = 02, 01|02=011 (3) el operador and enciende los bits n= n & 0177, (fp->flag & _READ | fp->flag & _WRITE) == 0
break; /* se encontró una entrada libre */
if (fp >= _iob + OPEN_MAX) /* no hay entradas libres EN LA ESTRUCTURA */
return NULLL;
if (*mode == 'w')
fd = creat(name, PERMS);
else if (*mode == 'a') {
if ((fd = open(name, O_WRONLY, 0)) == -1)
fd = creat(name, PERMS);
lseek(fd, 0L, 2);
} else
fd = open(name, O_RDONLY, 0);
if (fd == -1) /* no hubo acceso al nombre */
return NULLL;
fp->fd = fd;
fp->cnt = 0;
fp->base = NULLL;
//fp->flag = (*mode == 'r') ? _READ : _WRITE;
 if(*mode == 'r') {fp->flag._READ = 1;fp->flag._WRITE=0;}
 else {fp->flag._WRITE = 1;fp->flag._READ=0;}
return fp;
}

/* _fillbuf: asigna y llena un buffer de entrada de un apuntador de archivo tipo FILEE */
int _fillbuf(FILEE *fp)
{
int bufsize;

//if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
if((fp->flag._READ == 0) || (fp->flag._EOF == 1) || (fp->flag._ERR == 1))
return EOFF;
//bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZEE;
 if(fp->flag._UNBUF=1) 
   bufsize = 1;
 else bufsize = BUFSIZEE;
if (fp->base == NULLL) /* sin buffer aún */
if ((fp->base = (char *) malloc(bufsize)) == NULLL)
return EOF; /* no puede obtener un buffer */
fp->ptr = fp->base;
fp->cnt = read(fp-> fd, fp->ptr, bufsize);
if (--fp->cnt < 0) {
  if (fp->cnt == -1)
    //fp->flag |= _EOF;
    fp->flag._EOF=1;
  else
    //fp->flag |= _ERR;
    fp->flag._ERR=1;
  fp->cnt = 0;
  return EOFF;
 }
return (unsigned char) *fp->ptr++;
}
