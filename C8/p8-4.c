/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 8.4 */

/*
Programa que diseña e implementa _flushbuf, fflush, fclose 
para la estructura FILEE

_flushbuf(FILEE *fp): vacia el bufer del apuntador 
fflush
fclose(FILEE *fp) ; Libera la memoria asignada a la estructura apuntada por fp.
 
*/

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
int _flushbuf(int , FILEE *); //Para introducir el caracter al buffer de fp
FILEE *fopenn(char *, char *); //Definicion de fopenn
int fclosee(int , FILEE *); //para cerrar el descriptor de archivo y liberar el buffer


#define feof(p)   (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0) ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
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
	if(fclosee(fp)==0) printf("Archivo cerrado \n"),
	  else printf("No se logro cerrar el archivo\n");
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
return EOFF; /* no puede obtener un buffer */
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

/*_flushbuf: Pone el caracter x en el buffer si es que este tiene espacio*/
int _flushbuf(int x, FILEE *fp)
{
  unsigned nc;
  int bufsize;
  if(fp < iop || fp >= iop + OPEN_MAX) //el apuntador no esta en el rango de archivos a abrir
    return EOFF;
  if(fp->flag._WRITE == 0 || fp->flag._ERR == 1)
    return EOFF;
  if(fp->flag._UNBUF==1) bufsize = 1; else  bufsize = BUFSIZEE;
  if(fp->base == NULL){
    if((fp->base = (char *) malloc(bufsize))==NULL){
      fp->flag._ERR=1;
      return EOFF;
    }
  } else{ //el buffer ya existe 
    nc = fp->ptr - fp->base //los apuntares se pueden restar y dan el tamaño que queda 
      if(write(fp-fd, fp->base,nc) != nc)
	{
	fp->flag._ERR=1;
	return EOFF;
	}
}
  fp->ptr = fp->base;
  *fp->ptf++=(char) x;
  fp->cnt = bufsize-1;
  return x
}

/*fclose: La función fclose retorna cero si el stream fue cerrado con exito. 
Si se detectaron errores, entonces retorna EOF. */
int fclosee(int , FILEE *fp); //PARA VACIAR EL BUF?
{
  //liberamos el buffer en su campo fp->base
  free(fp->base)
    //cerramos el archivo correspondiente al descriptor
    if(close(fp->fd)==0)
      return 0;
    else return EOFF
}


/* fflush : flush buffer asociado con fp*/
int fflush(FILEE *fp)
{
  int rc = O;
   if(fp < iop || fp >= iop + OPEN_MAX) //el apuntador no esta en el rango de archivos a abrir
    return EOFF;
if(fp->flag._WRITE=1) 
  rc=_flushbuf(0,fp);
 fp->ptr=fp->base;
 if(fp->flag._UNBUF) fp->cnt=1; else fp->cnt=BUFSIZEE;
 return rc;
}


/*fseek: */

int fseek(FILEE *fp, long offset, int origin)
{
  unsigned nc;
  long rc;

  if(fp->flag._READ==1){
    if(origin==1)
      offset -= fp->cnt;
  rc=lseek(fp->fd,offset,origin);
    fp->cnt=0;  
  } else if(fp->flag._WRITE){
    if((nc->fp->ptr-fp->base)>0)
      if(write(fp->fd,fp->base,nc)!=nc)
	 rc=-1;
	 if(rc!=-1)
	   rc=lseek(fp->fd,offset,origin);
	 }
    return (rc==-1)? -1 :0;
  }
