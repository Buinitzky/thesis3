/* 
 * File:   CSimpleList.h
 * Author: Pedro Guarimata
 *
 * Created on 29 de enero de 2015, 05:04 PM
 * 
 * Estructura para el almacenamiento de cadenas de caracteres de forma dinámica.
 * se implementa una lista simple con un solo enlace entre nodos.
 */

#ifndef SIMPLELIST_H
#define	SIMPLELIST_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdlib.h>
#include <stdio.h>


    typedef struct SLNodo {
        void *value;
        struct SLNodo *next;
    } SLNodo;

    typedef struct SimpleList {
        /**
         * mantiene la cantidad de elementos que se encuentran en la lista.
         */
        int size;
        
        /**
         * contiene el valor del ultimo indice que se buscó en la lista.         
         */
        int last_index;
        
        /**
         * apunta al primer elemento de la lista.s
         */
        SLNodo *firts;
        
        /**
         apunya al último elemento de la lista.
         */
        SLNodo *last;
        /**
         * matiene la referencia del ultimo elemento indexado por getbyIndex
         * esto para hacer eficiente el recorrido del la lista si se hace con un
         * arreglo
         */
        SLNodo *last_indexed;
        
    } SimpleList;

    
    /**
     * Crea una nueva "instacia" de SimpleList, reserva la memoria necesaria
     * y retorna el objeto creado.
     * @return nueva estrutura SimpleList.
     * @author Pedro Guarimata.
     */
    SimpleList *createList();

    /**
     * Indica si la lista esta vacia o contiene algún elemento.
     * @param list apuntador a la lista evaluada.
     * @return true si la lista está vacia.
     */
    int isEmpty(SimpleList *list);

    /**
     * Inserta una nueva elemento al inicio de la lista indicada.
     * @param list apuntador a la estructura donde se hará la insercion.
     * @param item apuntador al nuevo elemento de la cadena.
     * @return 1 si es insertada, 0 si la operacion no es realizada.
     */
    int addFirtsItem(SimpleList *list, void *item);

    /**
     * Inserta una nueva elemento al final de la lista indicada.
     * @param list apuntador a la estructura donde se hará la insercion.
     * @param item apuntador al nuevo elemento de la cadena.
     * @return 1 si es insertada, 0 si la operacion no es realizada.
     */
    int addItem(SimpleList *list, void *item);
    
    /**
     * Retorna el elemento que se encuentre en la posición indicada por el index
     * @param list lista donde se hará la búsqueda.
     * @param index ubicación del elemento solicitado.s
     * @return apuntador al primer caracter de la cadena que se en cuentre en el
     * indice indicado.
     */
    void *get(SimpleList *list, int index);

    /**
     * Muestra los items almacenados en la lista 1 por una para esto necesita
     * de la un apuntador a la función que mostrará cada elemento esto por 
     * razones de la realización genérica.
     * @param list lista a mostrar
     * @param show funcion que se encarga de mostrar los items indicados.
     * @return 1 si se completo la operacion, 0 si hubo un error.
     */
    int showList(SimpleList *list, void (*show)(void *));

    /**
     * mustra una cadena de caracteres por la salida estandar
     * @param str apuntador a la cadena
     */
    void showChars(char *str);

    
#ifdef	__cplusplus
}
#endif

#endif	/* SIMPLELIST_H */

