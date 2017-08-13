/* 
 * File:   main.cpp
 * Author: administrador
 *
 * Created on 30 de julio de 2013, 14:12
 */

//#include <time.h>


#include <cstdlib>
#include <math.h> 
#include <wait.h>
#include <unistd.h>
//#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
using namespace std;

/*
 * 
 */
/****************MODIFICADO****************/
void leerArchivo(char* nombre_archivo, float* datos ){
    fstream archivo(nombre_archivo);
    float aux;
    int i=0;
    while(archivo>>datos[i++]);
        
    archivo.close();
}

int main(int argc, char** argv) {
    int cantP=0,hijo;
    float datos[5], trabajos, segCarga;
    leerArchivo("Archivos/entradaG",datos);
    trabajos = 1;//valores[2] / valores[0];
     segCarga =1;//valores[2] / valores[1];
    pid_t pid;
    /****************MODIFICADO****************/
    for(int j=0;j<datos[2]/segCarga;j++) {
        usleep(segCarga * 1000000);
        for(int i=0;i<trabajos;i++){
            cantP++;
            pid = fork();
            switch (pid) {
                case -1:
                    perror("\nNo se puede crear proceso\n");
                    return -1;
                case 0:
                    execl("./carga",NULL);
                    perror("\nError ejecucion\n");
                    exit(-1);
                    break;
            }
        }
               
    }
    for(int i=0;i<cantP;i++){
        wait(&hijo);
    }
    return 0;
}

