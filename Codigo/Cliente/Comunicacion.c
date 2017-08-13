#include <Socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void enviarDatos(int fd, char *Datos){
    char aux[15];
    int longitud=strlen(Datos),a;

    sprintf(aux, "%d", longitud);   
    Escribe_Socket(fd,aux,2);
    //printf("\nE: %s , %d\n",aux,a);
    Escribe_Socket(fd,Datos,longitud+1);
    //printf("\nE: %s , %d\n",Datos,a);
}

void recibirDatos(int fd, char *Datos){
    char aux[15];
    int a;
    while(Lee_Socket(fd,aux,2)==-1);
    //printf("\nR: %s, %d\n",aux,a);
    while(Lee_Socket(fd,Datos,atoi(aux))==-1);
    //printf("\nR: %s, %d\n",Datos,a);
    
}
