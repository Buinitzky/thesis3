#include <string.h>

#include "PConfigCluster.h"

SimpleList *createClusterGroups(int l, int npg, char *root, SimpleList *ips);

Cluster *initCluster(int nodos_grupo) {
    SimpleList *ips = getIpsMosix();
    return createCluster(nodos_grupo, ips);
}

Cluster *createCluster(int npg, SimpleList *ips) {
    Cluster *cluster = calloc(1, sizeof (Cluster));
    cluster->l = ips->size;
    cluster->npg = npg;
    cluster->ips = ips;
    cluster->root = ips->firts->value;
    cluster->grupos = createClusterGroups(cluster->l, npg, cluster->root, cluster->ips);
    return cluster;
}

Cluster *createEmptyCluster() {
    Cluster *cluster = calloc(1, sizeof (Cluster));
    cluster->l = 0;
    cluster->npg = 0;
    cluster->ips = createList();
    cluster->root = NULL;
    cluster->grupos = createList();
    return cluster;
}

//SimpleList *createClusterGroups(int l, int npg, char *root, SimpleList *ips) {
//    SimpleList *grupos = createList();
//    int num_groups = l / npg;
//    int ret_group = l % npg;
//    int i, j, limite;
//    for (i = 0; i < l; i++) {
//        SimpleList *list = createList();
//        char *ip = get(ips, i);
//        CGroup *grupo = createGroup(ip, list);
//        if (strcmp(ip, root) != 0) {
//            grupo->parent_ip = root;
//        }
//        limite = i + npg;
//        if (i == 0) {
//            limite = i + ret_group;
//        }
//        //el menos 1 es por que el 1 ya se agrega cuando se crea el grupo.
//        while (i < limite - 1) {
//            char *ip = get(ips, i + 1);
//            addItem(grupo->nodos, ip);
//            ++i;
//        }
//        addItem(grupos, grupo);
//    }
//    return grupos;
//}
SimpleList *createClusterGroups(int l, int npg, char *root, SimpleList *ips) {
    SimpleList *grupos = createList();
    int num_groups = l / npg;
    int ret_group = l % npg;
    int i, j, limite;
    for (i = 0; i < l; i++) {
        SimpleList *list = createList();
        char *ip = get(ips, i);
        CGroup *grupo = createGroup(ip, list);
        if (strcmp(ip, root) != 0) {
            grupo->parent_ip = root;
        }
        limite = i + npg;
        if ( limite > l) {
            limite = i + ret_group;
        }
        //el menos 1 es por que el 1 ya se agrega cuando se crea el grupo.
        while (i < limite - 1) {
            char *ip = get(ips, i + 1);
            addItem(grupo->nodos, ip);
            ++i;
        }
        addItem(grupos, grupo);
    }
    return grupos;
}

int saveCluster(Cluster *cluster, const char *file_name) {
    FILE *file;
    if (file = fopen(file_name, "w")) {
        fprintf(file, "%s %d %d %d\r\n", cluster->root, cluster->l, cluster->npg, cluster->grupos->size);
        SLNodo *nodo = cluster->grupos->firts;
        while (nodo != NULL) {
            fputCGroupStream((CGroup *) nodo->value, file);
            fputs("\r\n", file);
            nodo = nodo->next;
        }
        if (fclose(file)) {
            printf("\nPConfigCluster.saveCluster: Error al cerrar archivo: %s\n", file_name);
            return 0;
        }
        printf("PConfigCluster.saveCluster::se guardo la información del cluster en el archivo indicado.");
        return 1;
    } else {
        printf("PConfigCluster.saveCluster: error no se pudo abrir el archivo indicado.");
        return 0;
    }
}

Cluster *readClusterFile(const char *file_name) {
    FILE *file;
    if (file = fopen(file_name, "r")) {

        Cluster *cluster = createEmptyCluster();
        cluster->root = calloc(15, sizeof (char));
        int count = 0;
        int a = fscanf(file, " %s %d %d %d ", cluster->root, &cluster->l, &cluster->npg, &count);
        while (count > 0) {
            CGroup *group = fgetCGroupStream(file);
            showCGroup(group);
            addItem(cluster->grupos, group);
            --count;
        }
        fclose(file);
        return cluster;
    } else {
        printf("PConfigCluster.readClusterFile: error no se pudo abrir el archivo indicado.");
        return NULL;
    }
    return NULL;
}

CGroup *getGroupByIP(Cluster *cluster, char *ip) {
    SLNodo *nodo = cluster->grupos->firts;
    while (nodo != NULL) {
        CGroup *grupo = (CGroup *) nodo->value;
        if (strcmp(ip, grupo->ip) == 0)
            return grupo;
        nodo = nodo->next;
    }
    return NULL;
}

void showCluster(Cluster *item) {
    printf("información del cluster:\nnodos: %d", item->l);
    printf("\nnodos por grupo: %d", item->npg);
    printf("\nroot: %s", item->root);
    puts("\nips\n");
    showList(item->ips, (void (*)(void *))showChars);
    puts("division lógica:\n");
    showList(item->grupos, (void (*)(void *))showCGroup);
}
