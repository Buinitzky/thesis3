



#include "Conexiones.h"
#include "ServerCluster.h"

//int enviarBanderaUDP(char *ip, char *bandera, int puerto) {
//    int descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//    if (descriptor != -1) {
//        struct sockaddr_in *serv_addr = calloc(1, sizeof (sockaddr_in));
//        serv_addr->sin_family = AF_INET;
//        serv_addr->sin_port = htonl(puerto);
//        if (inet_aton(ip, &serv_addr->sin_addr) == 0) {
//            fprintf(stderr, "inet_aton() failed\n");
//            exit(1);
//        }
//
//        if (sendto(descriptor, bandera, 512, 0, (struct sockaddr*) serv_addr, sizeof (sockaddr_in)) == -1) {
//            perror("Conexiones.c::enviarBanderaUDP");
//        }
//        close(descriptor);
//        return 0;
//    }
//    return -1;
//}
//
//int ListenviarBanderaUDP(SimpleList *list, char *bandera, int puerto) {
//    if (list != NULL) {
//        SLNodo nodo = list->firts;
//        while (nodo != NULL) {
//            enviarBanderaUDP((char *) nodo->value, bandera, puerto);
//            nodo = nodo->next;
//        }
//        return 1;
//    }
//    return 0;
//}

void pruebaConexion() {

    struct protoent *ppe;
    ppe = getprotobyname("tcp");
    if(ppe == NULL){
        perror("Erro al intentar abrir el protocolo");
        exit(EXIT_SUCCESS);
    }
    puts("prueba conexion.\n");
    printf("prueba conexion: %s, %d\n", ppe->p_name, ppe->p_proto);
   
    int sock_descriptor;
    sock_descriptor = socket(AF_LOCAL,SOCK_DGRAM,0);
    if(sock_descriptor < 0){
        perror("Conexiones.pruebaConexion();\n error al abrir el descriptor:");
        exit(EXIT_SUCCESS);
    }
    puts("se abrio el descriptor.");
    close(sock_descriptor);
    
    struct servent *serv;
    serv = getservbyname("cpp_java",ppe->p_name);
    if(serv == NULL){
        perror("Conexiones.pruebaConexion();\n error al abrir el servicio:");
        exit(EXIT_SUCCESS);
    }
   
    
    
    printf("\nservicio: %s puerto: %d\n", serv->s_name, serv->s_port);
}

