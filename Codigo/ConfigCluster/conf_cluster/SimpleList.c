/* 
 * File:   SimpleList.c
 * Author: Pedro Guarimata
 *
 * Created on 29 de enero de 2015, 05:04 PM
 */
#include <bits/errno.h>

#include "SimpleList.h"

SimpleList *createList() {
    SimpleList *list = calloc(1, sizeof (SimpleList));
    list->size = list->last_index = 0;
    list->firts = list->last = list->last_indexed = NULL;
    return list;
}

int isEmpty(SimpleList *list) {
    if (list == NULL) {
        return 1;
    } else {
        if (list->size == 0) {
            return 1;
        } else {
            return 0;
        }
    }
}

int addFirtsItem(SimpleList *list, void *item) {
    if (item != NULL && list != NULL) {
        SLNodo *nodo = calloc(1, sizeof (SLNodo));
        nodo->next = list->firts;
        nodo->value = item;
        list->firts = nodo;
        list->size += 1;
        if (isEmpty(list)) {
            list->last = nodo;
        }
        return 1;
    }
    return 0;
}

int addItem(SimpleList *list, void *item) {
    if (item != NULL && list != NULL) {
        SLNodo *nodo = calloc(1, sizeof (SLNodo));
        nodo->value = item;
        nodo->next = NULL;
        if (isEmpty(list)) {
            list->firts = list->last = nodo;
        } else {
            list->last->next = nodo;
            list->last = nodo;
        }
        list->size += 1;
        return 1;
    }
    return 0;
}

void *get(SimpleList *list, int index) {
    if (isEmpty(list))
        return NULL;
    if (index >= 0 && index < list->size) {
        SLNodo *nodo = list->firts;
        int n = 0;
        if (index >= list->last_index && list->last_indexed != NULL) {
            nodo = list->last_indexed;
            n = list->last_index;
        }
        while (nodo != NULL) {
            if (n == index) {
                list->last_index = n;
                list->last_indexed = nodo;
                return nodo->value;
            }
            nodo = nodo->next;
            ++n;
        }
    }
    return NULL;
}



int showList(SimpleList *list, void (*show)(void *)) {
    if (list == NULL)
        return 0;
    SLNodo *nodo = list->firts;
    while (nodo != NULL) {
        (*show)(nodo->value);
        nodo = nodo->next;
    }
    return 1;
}

void showChars(char *str) {
    printf("%s\n", str);
}
