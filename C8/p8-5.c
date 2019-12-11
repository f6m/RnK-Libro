/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 8.5 */

//LLamadas al sistema: stat
//Las funciones opendir,closedir,readdir ya existen en C en la librera <dirent.h>
//Las estructuras DIR se detectaron ya en dirent.h. Este ejercicio esta realizando de nuevo 
//opendir,readdir,closedir, por eso las renombramos duplicando la ultima letra
// #include <sys/types.h>
// Tenemos errores al abir el archivo "." y procesar la recursion en sus subarchivos.
//Las definiciones
/*

DIR
    A type representing a directory stream. 

It also defines the structure dirent which includes the following members:


ino_t  d_ino       file serial number
char   d_name[]    name of entry

The type ino_t is defined as described in <sys/types.h>.

The character array d_name is of unspecified size, but the number of bytes preceding the terminating null byte will not exceed {NAME_MAX}. 

http://man7.org/linux/man-pages/man3/readdir.3.html

Para DIR en https://github.com/tronkko/dirent/blob/master/include/dirent.h
se indica que DIR tiene esta definicion en dirent.h:

struct DIR {
    struct dirent ent;
    struct _WDIR *wdirp;
};
typedef struct DIR DIR;

En stackoverflow manifiestan este error: https://stackoverflow.com/questions/9537352/reading-a-directory-file-in-c

https://pubs.opengroup.org/onlinepubs/000095399/basedefs/dirent.h.html
BUSCAR LA DECLARACION INTERNA DE la funcion readdir

The compiler does not need code, it only needs to know the names and arguments. The actual code is in a separate .lib file, and it's the linker's responsibility to locate it.

obs1: El programa no se mete recursivamente a listar todos los archivos de los subdirectoriois. solo los trata como archivos. (Falta agregar la bandera -r)
obs2: para esta modificacion fue valioso la documentacion linux de getdents y su ejemplo.
*/

#define _GNU_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/dir.h> //estructura local del directorio
#include <time.h>
#include <stdlib.h>
#include <unistd.h> //para read/open
#include <dirent.h>     /* Defines DT_* constants */
       

#define NAME_MAXX 14 //nombre del archivo mas grande
#define BUF_SIZE 1024

struct linux_dirent {
           long           d_ino;
           off_t          d_off;
           unsigned short d_reclen;
           char           d_name[];
       };

int bpos=0; //buffer pos : para ir cambiando la posicion del las estructuras del directorio

//Revisar estas estructuras en la definicion original señalada en: dirent.h
 typedef struct{
long ino; //NODO-i
char name[NAME_MAXX+1]; //nombre
} Dirent;


typedef struct{
  int fd; //descriptor de archivo para el directorio
Dirent d; //nodoi + nombre
} DIRR;

DIRR *opendire(char *);
Dirent *readdire(DIRR *);
Dirent *readdire2(DIRR *dp, char *, int);
void closedire(DIRR *);

#ifndef DIRSIZ
#define DIRSIZ 14 //tamaño maximo para el nombre del directorio
#endif 

//la llamada al sistema stat toma un nombre de archvo y regresa
//la informacion que esta en el nodo-i para ese archivo o -1 si existe un error
//char *nombre; struct stat stbuf; int stat(char *, struct stat *)
//stat(nombre,&strbuf) llena la estructura strbuf con la infomacion del nodo-i para nombre

//funcion principal para obtener el tamaño y nombre del archivo.
void fsize(char *);
void dirwalk(char *dir, void (*fcn)(char *));
void dirwalk2(char *dir, void (*fcn)(char *));

char *formatdate(char *str, time_t val)
{
  strftime(str,36,"%d.%m.%Y %H:%M:%S",localtime(&val));
  return str;
}
main(int argc, char **argv)
{
if(argc == 1)
  fsize("."); //procesa el directorio actual
 else while(--argc>0) //si no procesa cada uno de los archivos enviados
	fsize(*++argv);
 return 0;	
}

void fsize(char *name)
{
struct stat stbuf; //parametros del archivo en tipo estructura
 char date[36]; //para darle formato a las impresiones de la informaicon de los tiempos de acceso al archivo

if (stat(name,&stbuf)==-1) //llamada al sistema
{
 fprintf(stderr,"fsize: no se tiene acceso a %s\n",name);
	return;
}
// S_IMFT es la bandera en octal para el tipo de archivo como S_IFDIR es la bandera
//que indica si es dirctorio en la estructura stbuf devuelta por stat, el operador 
// & es el and a nivel de bits, estas son algunas banderas para el campo st_mode
if((stbuf.st_mode & S_IFMT)==S_IFDIR) //se enmascara con S_IFMT y revisa si la estructura de sistema en st_mode 
  dirwalk2(name,fsize); //puntero a funcion
        printf("Archivo: %s\n",name);
	printf("[dev_t st_dev](dispositivo de nodo i) %8ld\n",stbuf.st_dev); 
	printf("[ino_t st_ino](# de nodo i) %8ld\n",stbuf.st_ino); 
	printf("[ino_t st_mode](bits de modo-octal) %o\n",stbuf.st_mode); 
	printf("[ino_t st_nlink](# ligas al archivo) %8ld\n",stbuf.st_nlink); 
	printf("[ino_t st_uid](id del usuario de propietario) %8i\n",stbuf.st_uid); 
	printf("[ino_t st_gid](id del grupo del propietario) %8i\n",stbuf.st_gid); 
	printf("[ino_t st_rdev](para archivos especiales) %8ld\n",stbuf.st_rdev); 
	printf("[ino_t st_size](tam. en #caracteres) %8ld\n",stbuf.st_size); 
	printf("[ino_t st_atime](hr. de ultimo acceso) %s\n",formatdate(date,stbuf.st_atime)); 
	printf("[ino_t st_mtime](hr. de la ultima modif.) %s\n",formatdate(date,stbuf.st_mtime)); 
	printf("[ino_t st_ctime](hr. de creacion original) %s\n",formatdate(date,stbuf.st_ctime)); 
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{

char name[MAX_PATH];
Dirent *dp;
DIRR *dfd;

 if((dfd = opendire(dir)) == NULL){ //abre el directorio
	fprintf(stderr,"dirwalk: no se puede abrir %s\n",dir);
	return;
}
 while((dp = readdire(dfd)) != NULL){
    if(strcmp(dp->name,".") == 0 || strcmp(dp->name,"..") == 0) //se ignora asi mismo y asu padre
	continue;
	if(strlen(dir) + strlen(dp->name)+2>sizeof(name))
	fprintf(stderr,"dirwalk:nombre %s/%s demasiado largo\n",dir,dp->name);
	else{ 
	sprintf(name,"%s/%s",dir,dp->name);
	(*fcn)(name);//hace el recorrido leyendo cada archivo que encuentra y adentrandose es DFS
	}
	}
 closedire(dfd);
}

//version modificada de dirwalk, usando readdir2
void dirwalk2(char *dir, void (*fcn)(char *))
{
char dirbuf[BUF_SIZE];
char name[MAX_PATH];
Dirent *dp;
DIRR *dfd;
long int nbytes;

 if((dfd = opendire(dir)) == NULL){ //abre el directorio
	fprintf(stderr,"dirwalk: no se puede abrir %s\n",dir);
	return;
}
 if((nbytes=syscall(SYS_getdents,dfd->fd,dirbuf, sizeof(dirbuf))) > 0) //== sizeof(dirbuf)) //lo que se lee sea igual al tamaño del bufer
{
 while((dp = readdire2(dfd,dirbuf,nbytes)) != NULL){

   if(strcmp(dp->name,".") == 0 || strcmp(dp->name,"..") == 0) //se ignora asi mismo y asu padre
	continue;
	if(strlen(dir) + strlen(dp->name)+2>sizeof(name))
	fprintf(stderr,"dirwalk:nombre %s/%s demasiado largo\n",dir,dp->name);
	else{ 
	sprintf(name,"%s/%s",dir,dp->name);
	(*fcn)(name);//hace el recorrido leyendo cada archivo que encuentra y adentrandose es DFS
	} //end-else
	} //end-while
}//end-if
 closedire(dfd);
}

// int fstat(int fd, struct stat *) es como stat solo que requiere un descriptor de archivo
DIRR *opendire(char *dirname){
int fd;
struct stat stbuf;
DIRR *dp;
 if((fd=open(dirname, O_RDONLY,0)) == -1 //si no se pudo abrir el archivo
    || fstat(fd,&stbuf) == -1 //no se logro obtener la informacion con fstat
    || (stbuf.st_mode & S_IFMT) != S_IFDIR //no es un directorio
    || (dp = (DIRR *)malloc(sizeof(DIRR))) == NULL) //no se logro reservar la memoria demandada para la estructura
   return NULL; //termina
dp->fd=fd;
 return dp; //regresa la estructura
}
// closedir: cierra el directorio abierto por opendir
void closedire(DIRR *dp)
{
if(dp){
close(dp->fd);
free(dp);
}
}

// El descriptor que envia para abir "." es el primero disponible 0-stdin 1-stdout 2-stderr
// el primero disponible es el 3, open esta bien el que no funciona es read.
Dirent *readdire(DIRR *dp)
{
//struct direct dirbuf; //Estructura local del directorio dir.h, ES DIRECT O DIRENT, ambas estructuras existen!!!
char dirbuf[BUF_SIZE];
static Dirent d;
struct linux_dirent *D;
long int nbytes;
 //nbytes=syscall(SYS_getdents,dp->fd,dirbuf, sizeof(dirbuf)); //264 bytes 

 while((nbytes=syscall(SYS_getdents,dp->fd,dirbuf, sizeof(dirbuf))) != -1) //== sizeof(dirbuf)) //lo que se lee sea igual al tamaño del bufer
{
  printf("fd: %d bytes leidos: %ld\n",dp->fd,nbytes);
	D=(struct linux_dirent *)(dirbuf + bpos);
  printf("fd: %d nombre archivo: %s\n",dp->fd,(char *) D->d_name);
if(D->d_ino == 0) //enterada que no esta en uso
	continue;
d.ino = D->d_ino;
strncpy(d.name,D->d_name,D->d_reclen);
if(bpos < nbytes) bpos += D->d_reclen;
d.name[DIRSIZ] = '\0'; //terminacion del nombre
return &d;
}
return NULL;
}

// El descriptor que envia para abir "." es el primero disponible 0-stdin 1-stdout 2-stderr
// el primero disponible es el 3, open esta bien el que no funciona es read.
Dirent *readdire2(DIRR *dp, char *b, int nbytes)
{
//struct direct dirbuf; //Estructura local del directorio dir.h, ES DIRECT O DIRENT, ambas estructuras existen!!!

static Dirent d;
struct linux_dirent *D;

 //nbytes=syscall(SYS_getdents,dp->fd,dirbuf, sizeof(dirbuf)); //264 bytes 

while(bpos < nbytes)
 {
  D=(struct linux_dirent *)(b + bpos);
  printf("fd directorio: %d nombre archivo: %s\n",dp->fd,(char *) D->d_name);
if(D->d_ino == 0) //enterada que no esta en uso
	continue;
d.ino = D->d_ino;
strncpy(d.name,D->d_name,D->d_reclen);
bpos += D->d_reclen;
d.name[D->d_reclen] = '\0'; //terminacion del nombre
return &d;
} //end-if bpos
return NULL;
} 

