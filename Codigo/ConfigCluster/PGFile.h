/* 
 * File:   PGFile.h
 * Author: Pedro Guarimata
 *
 * Created on 29 de enero de 2015, 05:35 PM
 */

#ifndef PGFILE_H
#define	PGFILE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "SimpleList.h"
    

/**
 * Carga en una estructura CSimpleList los ips que se en cuentran almacenados en 
 * en el archiv mosix.map se asume que en ese archivo se encuentran los ips de
 * todos los nodos del cluster.
 * @return CSimpleList que almacenas los ips registrados en el mosix.map
 */
 SimpleList *getIpsMosix();
 
 /**
  * Lee todas las lineas de de un archivo y las retorna en una lista simple.
  * @param file_name
  * @return 
  */
 SimpleList *getLinesFile(const char *file_name);

#ifdef	__cplusplus
}
#endif

#endif	/* PGFILE_H */

