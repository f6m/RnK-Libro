/* El lenguaje de programacion C, R&K, (Prentice Hall, 2da. edicion, 1991) */
/* # 8.1 */

/*
programa que implementa la version de cat en terminos de las funciones
read y write, close, open

¿Que funcion es mas rapida, la cat de la pag. 180 o esta version?
Esta version, no ocupa funciones auxiliares como filecopy y es mas corta,
trabaja directamente con los bytes E/S a copiar.

Descriptores de archivos estandares: 0 entrada, 1 salida, 2 error */

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

#define PERMS O666

main(int argc, char *argv[])
{
char buf[BUFSIZ];
void filecopy(FILE *, FILE *);
char *prog = argv[0]; //nombre del programa
int fp,n;

if(argc == 2){ //Si no se invoca con prog file1 file2 
	if((fp = open(argv[1],O_RDONLY,0)) != -1){ //open regresa descriptor de archivo 
	n=read(fp,buf, sizeof buf);
	write(1,buf,n);
	}
	else error("cat: %s nos se puede abrir %s\n",prog,argv[1]);
}
else while(--argc > 0)
	if( (fp = open(*++argv,O_RDONLY,0)) != -1){ //el tercer argumento de open es 0(perms), fp tiene el descriptor del archivo leido
	if ((n=read(fp,buf, sizeof buf))!=-1) //lee fp y coloca en buf otorgando el numero n de bytes leidos
	write(1,buf,n); //escribe lo que tiene buf n bytes en la salida estandar pantalla 1
	else {
	error("cat: %s no pudo leer %s\n ",prog,*argv);	
	exit(1);
	}
	close(fp); //cerramos el archivo abierto con descriptor fp
	} else{ 
	error("cat: %s nos se puede abrir %s\n",prog,*argv);
	exit(1);
	}
exit(0);
}

