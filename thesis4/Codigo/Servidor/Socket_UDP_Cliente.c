
//UDPClient.c

/*
 * gcc -o client UDPClient.c
 * ./client <server-ip>
 */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFLEN 512
#define PORT 9930

void err(char *s) {
    perror(s);
    /*
        exit(1);
     */
}
int Enviar_Bandera_Servidor(char* ip, char* letra) {
    struct sockaddr_in serv_addr;
    int sockfd, i, slen = sizeof (serv_addr);
    char buf[BUFLEN];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        err("socket");

    bzero(&serv_addr, sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_aton(ip, &serv_addr.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    strcpy(buf, "./Servidor");
    strcat(buf, " ");
    strcat(buf, letra);
    printf("lo que envia en la bandera: %s", buf);
    perror("Error despues de enviar las banderas: ");
    while (1) {
        /*
                printf("\nEnter data to send(Type exit and press enter to exit) : ");
                scanf("%[^\n]", buf);
                getchar();
         */
        if (strcmp(buf, "exit") == 0)
            break;

        if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*) &serv_addr, slen) == -1)
            err("sendto()");
        strcpy(buf, "exit");
    }

    close(sockfd);
    return 0;
}
int Enviar_Bandera(char* ip) {
    struct sockaddr_in serv_addr;
    int sockfd, i, slen = sizeof (serv_addr);
    char buf[BUFLEN];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        err("socket");

    bzero(&serv_addr, sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_aton(ip, &serv_addr.sin_addr) == 0) {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    strcpy(buf, "./Cliente");
    while (1) {
        /*
                printf("\nEnter data to send(Type exit and press enter to exit) : ");
                scanf("%[^\n]", buf);
                getchar();
         */
        if (strcmp(buf, "exit") == 0)
            break;

        if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr*) &serv_addr, slen) == -1)
            err("sendto()");
        strcpy(buf, "exit");
    }

    close(sockfd);
    return 0;
}

