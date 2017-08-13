#include <string.h>

#include "CGroup.h"

CGroup *createGroup(char *ip, SimpleList *nodos) {
    CGroup *grupo = calloc(1, sizeof (CGroup));
    grupo->ip = ip;
    grupo->nodos = nodos;
    return grupo;
}

void showCGroup(CGroup *item) {
    printf("\nsub-root: %s\n", item->ip);
    printf("parent-root: %s \nips: \n", item->parent_ip);
    showList(item->nodos, (void (*)(void *))showChars);
}

void fputCGroupStream(CGroup *group, FILE *file) {
    fprintf(file, "p %s %d\r\n", group->parent_ip, group->nodos->size);
    fprintf(file, "s %s %d\r\n", group->ip, group->stable);
    SLNodo *nodo = group->nodos->firts;
    while (nodo != NULL) {
        fprintf(file, "l %s -\r\n", (char *) nodo->value);
        nodo = nodo->next;
    }
    printf("CGroup.fputCGroupStream: se guardo el grupo en el stream\r\n");
}

void fputCGroupIpsStream(CGroup *group, FILE *file) {
    if (group->parent_ip != NULL) {
        fprintf(file, "%s", group->parent_ip);
    }
    if (group->ip != NULL) {
        fprintf(file, "\r\n%s", group->ip);
    }
    SLNodo *nodo = group->nodos->firts;
    while (nodo != NULL) {
        fprintf(file, "\r\n%s", (char *) nodo->value);
        nodo = nodo->next;
    }
    printf("CGroup.fputCGroupStream: se guardo el grupo en el stream\r\n");

}

CGroup *fgetCGroupStream(FILE* file) {
    int size = 0;
    char *tipo = calloc(1, sizeof (char));
    char *info = calloc(1, sizeof (char));
    CGroup *group = createGroup(calloc(15, sizeof (char)), createList());
    char *ip = calloc(15, sizeof (char));
    fscanf(file, "%s %s %d", tipo, ip, &size);
    if (strcmp(tipo, "p") == 0 && strcmp(ip, "(null)") != 0) {
        group->parent_ip = ip;
    }
    fscanf(file, "%s %s %s", tipo, group->ip, info);
    while (size > 0) {
        ip = calloc(15, sizeof (char));
        fscanf(file, "%s %s %s", tipo, ip, info);
        addItem(group->nodos, ip);
        --size;
    }
    printf("CGroup.fgetCGroupStream: se leyó el grupo en el stream\r\n");
    return group;
}

CGroup *fgetCGroupIpsStream(FILE *file, int size_group) {
    CGroup *group = createGroup(calloc(15, sizeof (char)), createList());
    group->parent_ip = calloc(15, sizeof (char));
    fscanf(file, "%s", group->parent_ip);
    fscanf(file, "%s", group->ip);
    int count = 0;
    SLNodo *nodo = group->nodos->firts;
    while (count++ < size_group) {
        SLNodo *nodo = calloc(1, sizeof (SLNodo));
        nodo->value = calloc(15, sizeof (char));
        if (fscanf(file, "%s", (char *) nodo->value) != EOF)
            addItem(group->nodos, nodo);
    }
    printf("CGroup.fputCGroupStream: se guardo el grupo en el stream\r\n");

}

int saveCGroupFile(CGroup *group, const char *file_name) {
    FILE *file;
    if (file = fopen(file_name, "w")) {
        fputCGroupStream(group, file);
        fclose(file);
        return 1;
    } else {
        printf("CGroup.saveFile: error al intertar de abrir el archivo %s", file_name);
    }
    return 0;
}

int saveCGroupIpsFile(CGroup *group, const char *file_name) {
    FILE *file;
    if (file = fopen(file_name, "w")) {
        fputCGroupIpsStream(group, file);
        fclose(file);
        return 1;
    } else {
        perror("CGroup.saveCGroupIpsFile: ");
        return 0;
    }
    return 0;
}

CGroup *readCGroupFile(const char *file_name) {
    FILE *file;
    if (file = fopen(file_name, "r")) {
        CGroup *group = fgetCGroupStream(file);
        fclose(file);
        return group;
    } else {
        printf("CGroup.readCGroupFile: error al intertar de abrir el archivo %s", file_name);
    }
    return NULL;
}
