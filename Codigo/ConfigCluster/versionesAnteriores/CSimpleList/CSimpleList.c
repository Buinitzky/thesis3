/* 
 * File:   CSimpleList.c
 * Author: Pedro Guarimata
 *
 * Created on 29 de enero de 2015, 05:04 PM
 */
#include "CSimpleList.h"

struct CSimpleList createList() {
    struct CSimpleList *list = calloc(1,sizeof(struct CSimpleList));
    list->size = 0;
    list->firts = NULL;
    return *list;
}

int isEmpty(struct CSimpleList *list) {
    if (list == NULL) {
        return 1;
    } else {
        if ( list->size = 0) {
            return 1;
        } else {
            return 0;
        }
    }
}

int insertChars(struct CSimpleList *list, char *str) {
    if (str != NULL && list != NULL) {
        struct CNodo *nodo = calloc(1,sizeof(struct CNodo));
        nodo->next = list->firts;
        nodo->value = str;
        list->firts = nodo;
        list->size += 1;
        return 1;
    }
    return 0;
}

char *getByIndex(struct CSimpleList *list, int index) {
    if (index >= 0 && index < list->size) {
        struct CNodo *nodo = list->firts;
        int n = 0;
        while (n++ < index) {
            nodo = nodo->next;
        }
        return nodo->value;
    }
    return NULL;
}

int showList(struct CSimpleList *list) {
    if (list == NULL)
        return 0;
    struct CNodo *nodo = list->firts;
    while (nodo != NULL) {
        printf("caracteres: %s\n", nodo->value);
        nodo = nodo->next;
    }
    return 1;
}