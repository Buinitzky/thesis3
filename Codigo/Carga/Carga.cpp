/* 
 * File:   main.cpp
 * Author: administrador
 *
 * Created on 31 de julio de 2013, 12:23 PM
 */

#include <cstdlib>
#include <math.h>

#include <fstream>
#include <iostream>

using namespace std;


void procesar(int cantMB) {
    int mega = 1024 * 1024;
    int megaInt = mega / 4;
    int *p = new int[megaInt];
    for (int i = 0; i < megaInt; i++) {
        p[i] = rand() % 100;
    }
    if (cantMB > 1) 
        procesar(cantMB - 1);
    
    int k = 0;
    for(int i=0;i<mega;i++) 
        for(int j=0;j<2;j++){
         p[k] = sqrt(p[k]) * pow(p[k], 6);

          k = (k + 1) % megaInt;
        }
}



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
/****************MODIFICADO****************/
int main(int argc, char** argv) {
    
    float a[5];
    leerArchivo("Archivos/entradaG",a);
    procesar(a[1]);
    return 0;
}

