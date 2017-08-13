#include <arpa/inet.h>
#include <netdb.h>

#include "ServerCluster.h"

void ejecutar_accion(char *accion, char *parametros);

int openSocket(int familia, int tipo, int proto) {
    int sock = socket(familia, tipo, proto);
    if (sock == -1) {
        perror("ServerCluster.openSocket: erro al intentar abrir el socket.");
        return -1;
    }
    printf("\nsock ... [%d]", sock);
    return sock;
}

int bindToSocket(int sock_id, int puerto) {
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = puerto;
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_id, (struct sockaddr *) &addr, sizeof (addr)) == -1) {
        perror("ServerCluster.bindSock: erro al intentar enlazar el socket.");
        return -1;
    }
    puts("\nbind ... [ok]");

    return 0;
}

int getPortService(char *service, char *protocol) {
    struct servent *serv = getservbyname(service, protocol);
    if (serv == NULL) {
        puts("error");
        perror("ServerCluster.getPortServiceUdp: no se encontro el servicio udp");
        return -1;
    }
    printf("\nport ... [%d][%d]", ntohs(serv->s_port), serv->s_port);
    return serv->s_port;
}

int sendFlagToIpsList(SimpleList *list, char *flag) {
    puts("\nsending flag ... ");
    int sock = openSocket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
        return sock;
    struct sockaddr_in *saddr;
    saddr = calloc(1, sizeof (struct sockaddr_in));
    saddr->sin_family = AF_INET;
    saddr->sin_port = getPortService(SERV_UDP, "udp");
    SLNodo *nodo = list->firts;
    while (nodo != NULL) {
        char *ip = (char *) nodo->value;
        if (inet_aton(ip, &(saddr->sin_addr)) == 0) {
            perror("ServerCluster.sendFlag: tranform ip error");
            close(sock);
            return -1;
        }
        if (sendto(sock, flag, PACK_SIZE, 0, (struct sockaddr *) saddr, sizeof (*saddr)) == -1) {
            perror("ServerCluster.sendFlag: sendto flag error : ");
            close(sock);
            return -1;
        }
        nodo = nodo->next;
    }
    puts("[flags send]");
    shutdown(sock, 1);
    close(sock);
    return 0;
}

int initServiceSubRoots(Cluster *cluster, char *service_name) {
    puts("\ninit service...");
    int sock_id = openSocket(AF_INET, SOCK_DGRAM, 0);
    if (sock_id != -1) {
        struct sockaddr_in *serv;
        serv = calloc(1, sizeof (struct sockaddr_in));
        serv->sin_family = AF_INET;
        serv->sin_port = getPortService(SERV_UDP, "udp");
        SLNodo *nodo = cluster->grupos->firts;
        while (nodo != NULL) {
            CGroup *grupo = (CGroup *) nodo->value;
            if (inet_aton(grupo->ip, &(serv->sin_addr)) != 0) {
                size_t size_addr = sizeof (*serv);
                if (sendto(sock_id, service_name, PACK_SIZE, 0, (struct sockaddr *) serv, size_addr) == -1) {
                    perror("ServerCluster.initService:\n no se pudo enviar el mensaje.");
                    close(sock_id);
                    return -1;
                }
                nodo = nodo->next;
            } else {
                perror("ServerCluster.initServiceSubRoots\nno se pudo transformar la ip a formato binario:");
                return -1;
            }
        }
        puts("\ncomando enviado.");
        shutdown(sock_id, 1);
        close(sock_id);

        return 0;

    }
}



//queda esperando data.

int waitOrderFromRoot() {
    puts("\npreparando...");
    int socket = openSocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bindToSocket(socket, getPortService(SERV_UDP, "udp"));
    //listen(socket, 10);
    char buf[PACK_SIZE];
    struct sockaddr_in send_addr;
    socklen_t slen = sizeof (send_addr);
    puts("\nwaiting...");
    while (1) {
        memset(buf, 0, PACK_SIZE);
        if (recvfrom(socket, buf, PACK_SIZE, 0, (struct sockaddr*) &send_addr, &slen) == -1) {
            perror("ServerCluster.waitOrderFromRoot. error el recivir el packete");
        }
        printf("Paquete recivido: %s %d \nData: %s\n\n", inet_ntoa(send_addr.sin_addr), ntohs(send_addr.sin_port), buf);

        char *ip = calloc(15, sizeof (char));
        inet_ntop(AF_INET, &send_addr.sin_addr, ip, 15);
        ejecutar_accion(buf, ip);

    }
    shutdown(socket, 0);
    close(socket);

    return 0;
}

int waitSubRootsRecall(Cluster * cluster) {
    struct sockaddr_in addr;
    socklen_t len = sizeof (addr);

    int socket = openSocket(AF_INET, SOCK_STREAM, 0);
    int atendidos = 0;
    bindToSocket(socket, getPortService(SERV_TCP, "tcp"));
    if (listen(socket, cluster->grupos->size) == -1) {
        perror("ServerCluster. waitSubRootRecall: no es posible escuchar en ese puerto.");
        return -1;
    }
    char buffer[PACK_SIZE];
    while (atendidos < cluster->grupos->size - 1) {
        struct sockaddr_in sock_client;
        unsigned int addr_size = sizeof (sock_client);
        int conn = accept(socket, (struct sockaddr *) & sock_client, &addr_size);
        if (conn == -1) {
            perror("no se puede conectar al coket secundario");
        }
        puts("\nconexion de subroot aceptada");
        char *ip = calloc(15, sizeof (char));
        inet_ntop(AF_INET, &sock_client.sin_addr, ip, 15);
        puts(ip);
        CGroup *grupo = getGroupByIP(cluster, ip);
        int count_error = 0;
        if (grupo != NULL) {
            SLNodo *nodo = grupo->nodos->firts;
            while (nodo != NULL) {
                memset(ip, 0, 15);
                strcpy(ip, (char *) nodo->value);
                if (send(conn, ip, PACK_SIZE, 0) == -1) {
                    perror("ServerCluster.waitCallFromSR: error al enviar ip");
                    if (count_error++ == 10) {
                        shutdown(conn, 2);
                        close(conn);
                        printf("no se pudo enviar el ip %s.", ip);
                        return -1;
                    }
                } else {
                    printf("\nip %s enviado", ip);
                    nodo = nodo->next;
                }
            }
            memset(ip, 0, 15);
            strcpy(ip, "exits");
            if (send(conn, ip, PACK_SIZE, 0) == -1) {
                perror("ServerCluster.waitCallFromSR: error al enviar ip");
            }
            puts("\nconexion terminada.");
            shutdown(conn, 2);
            close(conn);
            ++atendidos;
        } else {
            shutdown(conn, 2);
            close(conn);
        }
    }
    close(socket);

    return 0;
}

CGroup * callRootForData(char *ip_root) {
    printf("\nnew call root %s", ip_root);
    puts("\n");
    CGroup *group = createGroup(calloc(15, sizeof (char)), createList());
    struct sockaddr_in addr;
    unsigned int size_addr = sizeof (addr);

    group->parent_ip = calloc(strlen(ip_root), sizeof (char));
    strcpy(group->parent_ip, ip_root);

    int socket = openSocket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = getPortService(SERV_TCP, "tcp");

    if (inet_aton(group->parent_ip, &(addr.sin_addr)) == 0) {
        perror("ServerCluster.callRootForData: error al realizar la transformación de la ip");
        return NULL;
    }

    int conn = connect(socket, (struct sockaddr *) &addr, size_addr);
    if (conn != -1) {
        char buf[PACK_SIZE];
        short count = 0;
        char *ip;
        while (count-- < 10) {
            memset(buf, 0, PACK_SIZE);
            if (recv(socket, buf, PACK_SIZE, 0) != -1) {
                ip = calloc(15, sizeof (char));
                int size = strlen(buf);
                puts("dato recibido");
                puts(buf);
                strncpy(ip, buf, size);
                if (strcmp(ip, "exits") != 0) {
                    addItem(group->nodos, ip);
                    printf("ip: %s add", ip);
                } else {
                    shutdown(socket, 2);
                    close(socket);
                    puts("datos guardados.");
                    return group;
                }

            } else {
                shutdown(socket, 2);
                close(socket);
                perror("ServerCluster.callRootForData: error al recibir la informacion");
                return NULL;
            }
        }
    }
    shutdown(socket, 2);
    close(socket);
    showCGroup(group);
    return group;

}

int bindLeafs(CGroup *grupo) {
    if (grupo != NULL) {
        return sendFlagToIpsList(grupo->nodos, "bindleaf");
    } else {
        puts("ServerCluster.bindLeads: el grupo es invalido valor NULL");
        return -1;
    }
}

void ejecutar_accion(char *accion, char *parametros) {
    char *comando = calloc(100, sizeof (char));
    int size = strlen(parametros);
    if (strcmp("cliente", accion) == 0) {
        comando = "./Cliente";
    } else if (strcmp("callroot", accion) == 0) {
        char *aux = "./configcluster callroot ";
        char *x = calloc(size, sizeof (char));
        strcpy(x, parametros);
        strcat(comando, aux);
        strcat(comando, x);
    } else if (strcmp("bindleaf", accion) == 0) {
        char *aux = "./configcluster bindleaf ";
        char *x = calloc(size, sizeof (char));
        strcpy(x, parametros);
        strcat(comando, aux);
        strcat(comando, x);
    }
    printf("[%s]", comando);
    puts("\n");
    system(comando);
}


