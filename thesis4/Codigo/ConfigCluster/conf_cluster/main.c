/* 
 * File:   main.c
 * Author: Pedro Guarimata
 *
 * Created on 29 de enero de 2015, 04:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "PGFile.h"
#include "PConfigCluster.h"
#include "Conexiones.h"
#include "ServerCluster.h"
#define MAX_CLIENTES 6
#define DEST_CLUSTER "./cluster.map"
#define DEST_IPS "./Archivos/ips.txt"
#define DEST_IPS_SROOT "./Archivos/ipsDeSubRoots.txt"

int menu();
Cluster *loadCluster(int size_groups);

int main(int argc, char** argv) {
    Cluster *cluster;
    int size_group = MAX_CLIENTES;
    int opc = 9;
    printf("main");
    if (argc == 1) {
        do {
            opc = menu("init");
            switch (opc) {
                case 1:
                {
                    loadCluster(size_group);
                    break;
                }
                case 2:
                {
                    size_group = menu("size");
                    loadCluster(size_group);
                    break;
                }
            }
        } while (opc != 9);
    } else {
        printf(" identificando parametro: %s", argv[1]);

        if (strcmp(argv[1], "waitroot") == 0) {
            waitOrderFromRoot();
        } else if (strcmp(argv[1], "callroot") == 0) {
            char *ip = calloc(strlen(argv[2]), sizeof (char));
            strcpy(ip, argv[2]);
            CGroup *grupo = callRootForData(ip);
            if (grupo != NULL) {
                saveCGroupIpsFile(grupo, DEST_IPS);
                bindLeafs(grupo);
            }
        } else if (strcmp(argv[1], "bindleaf") == 0) {
            char *ip = calloc(strlen(argv[2]), sizeof (char));
            strcpy(ip, argv[2]);
        }
    }



    return (EXIT_SUCCESS);
}

Cluster *loadCluster(int size_groups) {
    Cluster *cluster = initCluster(size_groups);
    showCluster(cluster);
    int save = menu("load");
    if (save == 1) {
        saveCluster(cluster, DEST_CLUSTER);
        initServiceSubRoots(cluster, "callroot");
        waitSubRootsRecall(cluster);
        saveRootGroupInfo(cluster);
    }
    return cluster;
}

int menu(const char *menu) {
    int opc = 0;
    if (strcmp(menu, "init") == 0) {
        puts("\n#configuración del cluster#");
        printf("1.- Cargar cluster desde mosix.map\n");
        printf("2.- Modificar tamaño de grupos y recargar cluster.\n");
        printf("9.- Salir\n:");
    } else if (strcmp(menu, "size") == 0) {
        puts("\ntamaño ");
    } else if (strcmp(menu, "load") == 0) {
        puts("\ndesea salvar el cluster? #esta operación módificará la configuración en todo el cluster\n( 1 = si, 0 = no )opc:");
    }
    while (opc < 1 || opc > 3) {
        printf("Opcion: ");
        scanf("%d", &opc);
        if (opc == 9)
            break;
    }
    return opc;
}

int saveParentLeaf(char *ip) {
    FILE *file;
    if (file = fopen(DEST_IPS, "w")) {
        fputs(ip, file);
        if (fclose(file)) {
            printf("\nmain.nPConfigClustersaveParentLeaf: Error al cerrar archivo: %s\n", DEST_IPS);
            return '1';
        }
        return 0;
    } else {
        perror("no se puedo abrir el archivo para almacenaje");
        return -1;
    }
}

int saveRootGroupInfo(Cluster *cluster) {
    CGroup *subroots = createGroup(NULL, createList());
    SLNodo *nodo = cluster->grupos->firts;
    while (nodo != NULL) {
        CGroup *grupo = (CGroup *) nodo->value;
        if (strcmp(grupo->ip, cluster->root) == 0) {
            saveCGroupIpsFile(grupo, DEST_IPS);
        }
        addItem(subroots->nodos, grupo->ip);
        nodo = nodo->next;
    }
    saveCGroupIpsFile(subroots, DEST_IPS_SROOT);
    return 0;
}


