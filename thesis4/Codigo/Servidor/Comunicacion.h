/* 
 * File:   Comunicacion.h
 * Author: administrador
 *
 * Created on 19 de julio de 2013, 06:08 AM
 */

#ifndef _COMUNICACION_H
#define	_COMUNICACION_H

void enviarDatos(int fd, char *Datos);
void recibirDatos(int fd, char *Datos);

#endif	/* COMUNICACION_H */

