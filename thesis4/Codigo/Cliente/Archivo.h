/* 
 * File:   Archivo.h
 * Author: administrador
 *
 * Created on 19 de julio de 2013, 12:51 AM
 */

#ifndef _ARCHIVO_H
#define	_ARCHIVO_H

void leerArchivo(char* nombre_archivo, float* datos );
int leerArchivoMOSIX(char* nombre_archivo,char** Cadena);
void escribirArchivo(char* nombre_archivo,char* contenido);
int leerIps(char* nombre_archivo, char** ips);

#endif	/* ARCHIVO_H */

