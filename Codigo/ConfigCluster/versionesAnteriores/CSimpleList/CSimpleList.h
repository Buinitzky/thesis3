/* 
 * File:   CSimpleList.h
 * Author: Pedro Guarimata
 *
 * Created on 29 de enero de 2015, 05:04 PM
 * 
 * Estructura para el almacenamiento de cadenas de caracteres de forma dinámica.
 * se implementa una lista simple con un solo link entre nodos.
 */

#ifndef CSIMPLELIST_H
#define	CSIMPLELIST_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <stdio.h>
    
    
    struct CNodo {
        char *value;
        struct CNodo *next;
    };

    struct CSimpleList {
        int size;
        struct CNodo *firts;
    };

    /**
     * Crea una nueva "instacia" de CSimpleList, reserva la memoria necesaria
     * y retorna el objeto creado.
     * @return nueva estrutura CSimpleList.
     * @author Pedro Guarimata.
     */
    struct CSimpleList createList();

    /**
     * Indica si la lista esta vacia o contiene algún elemento.
     * @param list apuntador a la lista evaluada.
     * @return true si la lista está vacia.
     */
    int isEmpty(struct CSimpleList *list);

    /**
     * Inserta una nueva cadena de caracteres al inicio de la lista indicada.
     * @param list apuntador a la estructura donde se hará la insercion.
     * @param str apuntador al primer elemento de la cadena.
     * @return 1 si es insertada, 0 si la operacion no es realizada.
     */
    int insertChars(struct CSimpleList *list, char *str);

    /**
     * Retorna el elemento que se encuentre en la posición indicada por el index
     * @param list lista donde se hará la búsqueda.
     * @param index ubicación del elemento solicitado.
     * @return apuntador al primer caracter de la cadena que se en cuentre en el
     * indice indicado.
     */
    char *getByIndex(struct CSimpleList *list, int index);

    /**
     * Muestra las cadenas de caracteres almacenadas en la lista 1 por una.
     * @param list lista a mostrar
     * @return 1 si se completo la operacion, 0 si hubo un error.
     */
    int showList(struct CSimpleList *list);

#ifdef	__cplusplus
}
#endif

#endif	/* CSIMPLELIST_H */

