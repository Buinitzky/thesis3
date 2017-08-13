
#include "PGFile.h"

SimpleList *getIpsMosix() {
    FILE* file;
    char *file_name = "/etc/mosix/mosix.map";
    SimpleList *list = createList();
    if (file = fopen(file_name, "r")) {
        char *ip;
        char aux[5];
        char nodos[5];
        while (!feof(file)) {
            ip = calloc(15, sizeof (char));
            fscanf(file, " %s %s %s ", ip, nodos, aux);
            addItem(list, ip);
        }
        if (fclose(file)) {
            printf("\nError al cerrar archivo: %s\n", file_name);
        }
        return list;
    }
    printf("\nError al abrir archivo: %s\n", file_name);
    return NULL;
}

SimpleList *getLinesFile(const char *file_name) {
    FILE *file;
    SimpleList *lines = createList();
    if (file = fopen(file_name, "r")) {
        char *line = NULL;
        size_t n = 0;
        ssize_t t;
        while (!feof(file)) {
            t = getline(&line, &n, file);
            addItem(lines, line);
        }
        if (fclose(file)) {
            printf("\nError al cerrar archivo: %s\n", file_name);
        }
        return lines;
    }
    printf("\nError al abrir archivo: %s\n", file_name);
    return NULL;
}


