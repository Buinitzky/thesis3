#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define MAXRECVSTRING 255  /* Longest string to receive */

void DieWithError(char *errorMessage)  /* External error handling function */
{
    puts(errorMessage);
}

int main(int argc, char *argv[])
{
    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast Address */
    unsigned short broadcastPort;     /* Port */
    char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
    int recvStringLen;                /* Length of received string */
    char signalControl;


    broadcastPort = 20333;   /* First arg: broadcast port */

    /* Create a best-effort datagram socket using UDP */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        DieWithError("socket() failed");

    /* Construct bind structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* Any incoming interface */
    broadcastAddr.sin_port = htons(broadcastPort);      /* Broadcast port */

    /* Bind to the broadcast port */
    if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0)
        DieWithError("bind() failed");

    /* Receive a single datagram from the server */
    while(1)
    {
        if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0)
        {
            //Al entrar aqui la conexion no se ha establecido.
            //Y no evalua los casos siguientes.
        }
        else
        {
            signalControl = recvString[recvStringLen-1];
            recvString[recvStringLen] = '\0';
            switch(signalControl)
            {
                case 'S':
                {
                    system ("clear");
                    printf("Arrancando evaluacion de subroot - Recibido: %s\n", recvString);    /* Print the received string */
                    signalControl = 'N';
                    system ("./Servidor S");
                    break;
                }
                
                case 'K':
                {
                    system ("clear");
                    printf("Estabilidad del cluster utilizando el metodo de Krasovskii en sub root - Recibido: %s\n", recvString);    /* Print the received string */
                    signalControl = 'N';
                    system ("./Servidor K");
                    break;
                }
                
                case 'M':
                {
                    system ("clear");
                    printf("Ejecutando generador de carga con MOSRUN sin migracion automatica (mosix) en sub root - Received: %s\n", recvString);    /* Print the received string */
                    signalControl = 'N';
                    system ("./Servidor M");
                    break;
                }
                
                case 'C':
                {
                    system ("clear");
                    printf("Ejecutando generador de carga con MOSRUN con migracion automatica (mosix) en sub root - Received: %s\n", recvString);    /* Print the received string */
                    signalControl = 'N';
                    system ("./Servidor C");
                    break;
                }
                
                case 'G':
                {
                    system ("clear");
                    printf("Calculando el tiempo de ejecucion de la carga (perf) en sub root - Received: %s\n", recvString);    /* Print the received string */
                    signalControl = 'N';
                    system ("./Servidor G");
                    break;
                }
                
                case 'E':
                {
                    system ("clear");
                    printf("Despertando Cliente - Received: %s\n", recvString);    /* Print the received string */
                    signalControl = 'N';
                    system ("./Cliente");
                    break;
                }
                
                default:
                    break;
            }
            if(signalControl == 'X') /* Si el servidor manda el 0 cierra los demonios en los clientes y quedan desconectados */
            {
                system ("clear");
                printf("Cerrando demonio (servicio) - Received: %s\n", recvString);    /* Print the received string */
                break;
            }
        }
    }
    close(sock);
    exit(0);
}
