/* 
 * File:   Conexiones.h
 * Author: Pedro Guarimata
 *
 * Created on 18 de febrero de 2015, 11:12 PM
 */

#ifndef CONEXIONES_H
#define	CONEXIONES_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include "SimpleList.h"
    
void pruebaConexion();

#ifdef	__cplusplus
}
#endif

#endif	/* CONEXIONES_H */

