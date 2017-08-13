
#include <Socket_Servidor.h>
#include <Socket.h>
#include <string.h>
#include <stdio.h>
#include <Archivo.h>
#include <Comunicacion.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <Recursos.h>
#include <Extras.h>
#include <time.h>
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdlib.h>     /* for atoi() and exit() */
#include <unistd.h>     /* for close() */
#include <Socket_UDP_Cliente.h>
#include <netdb.h>
#include <unistd.h>
#define MAX_IPS 10


int comparar(char* ip, char* ips) {
    int i = -1, aux = strlen(ips);
    while (i++<aux - 1) {
        //printf("\n'%c' = '%c'\n",ip[i],ips[i]);
        if (ip[i] != ips[i])
            return 0;
    }

    return 1;
}

int buscarID(char* ip, char** ips, int n) {
    int i = -1;

    while (i++<n) {
        if (comparar(ip, ips[i]))
            return i;
    }
    return -1;
}

comprobarIP(int id, int* clientes) {
    return clientes[id] == -1;

}

int establecerConexionCliente(int Socket_Servidor, int* Socket_Cliente, char* ip) {
    
    *Socket_Cliente = Acepta_Conexion_Cliente(Socket_Servidor, ip);
    if (*Socket_Cliente == -1) {
        printf("\nNo se puede abrir socket de cliente\n");
        return 0;
    };
    return 1;
}

int faltaIP(int cant_clientes_MOSIX, int* clientes, char** ips) {
    int i = 0;
    for (; i < cant_clientes_MOSIX; i++) {
        if (clientes[i] == -1) {
            return 1;
        }
    }
    return 0;
}

/****************MODIFICADO****************/
int establecerConexionesClientes(int cant_clientes_MOSIX, int Socket_Servidor, int* clientes, char** ips, char** datos) {
    int Socket_Cliente = -1, n = 0, id, r = 1;
    char* Cadena = calloc(100, sizeof (char));
    char* ip = calloc(15, sizeof (char));
    if (!establecerConexionCliente(Socket_Servidor, &Socket_Cliente, ip))
        return r;
    recibirDatos(Socket_Cliente, Cadena);
    id = buscarID(ip, ips, cant_clientes_MOSIX);
    datos[id] = Cadena;
    if (comprobarIP(id, clientes)) {
        clientes[id] = Socket_Cliente;
        n++;
        r = 0;
    } else {
        close(Socket_Cliente);
    }
    return r;

}
//nos busca el puerto a comunicarse
void establecerConexionServidor(int* Socket_Servidor) {
    *Socket_Servidor = Abre_Socket_Inet("cpp_java");
    if (*Socket_Servidor == -1) {
        printf("No se puede abrir socket servidor\n");
        exit(-1);
    }
}
void establecerConexionRoot(int* Socket_Con_Servidor,char* Cadena){
    *Socket_Con_Servidor = Abre_Conexion_Inet (Cadena, "cpp_java");
	if (*Socket_Con_Servidor == -1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
		exit (-1);
	}
}
void init(int* clientes) {
    int i = -1;
    while (i++<MAX_IPS) {
        clientes[i] = -1;
    }
}

/****************MODIFICADO****************/
int menu1() {
    int opc = 0;
    //system("clear");
    printf("1.- Analizar la estabilidad del cluster utilizando el metodo de Krasovskii\n");
    printf("2.- Ejecutar generador de carga con MOSRUN sin migracion automatica (mosix)\n");
    printf("3.- Ejecutar generador de carga con MOSRUN con migracion automatica (mosix)\n");
    printf("4.- Calcular el tiempo de ejecucion de la carga (perf)\n");
    printf("5.- Salir\n");

    while (opc < 1 || opc > 5) {
        printf("Opcion: ");
        scanf("%d", &opc);
    }
    return opc;
}
int menu() {
    int opc = 0;
    printf("1.- Configurar el Cluster\n");
    printf("2.- Iniciar descubrimiento de recursos\n");
    printf("3.- Ayuda\n");
    printf("4.- Salir\n");

    while (opc < 1 || opc > 4) {
        printf("Opcion: ");
        scanf("%d", &opc);
    }
    return opc;
}
void FinalizarConexionClientes(int* clientes, int cant_clientes) {
    int i = 0;
    for (; i < cant_clientes; i++) {
        close(clientes[i]);
        clientes[i] = -1;
    }
    printf("\nConexiones Finalizadas correctamente...\n");
}

/****************MODIFICADO****************/
void realizarconexiones(int cant_clientes_MOSIX, int Socket_Servidor, int* clientes, char** ips, char** datos) {

    char* Cadena = calloc(100, sizeof (char));
    int i;
    clock_t t0,tf;
    float d;
    for (i = 1; i < cant_clientes_MOSIX; i++) {
        Enviar_Bandera(ips[i]);
    }
    t0=time(0);   
    for (i = 1; i < cant_clientes_MOSIX; i++) {
        establecerConexionesClientes(cant_clientes_MOSIX, Socket_Servidor, clientes, ips, datos);
    }
    tf=time(0);
    d=difftime(tf, t0);
    printf("\nTiempo de recoleccion de recursos: %.2f seg\n",d);
    if (!faltaIP(cant_clientes_MOSIX, clientes, ips)) {
        for (i = 0; i < cant_clientes_MOSIX; i++) {
            strcat(Cadena, datos[i]);
            strcat(Cadena, " 1");
            strcat(Cadena, "\n");
        }
        printf("%s\n", Cadena);
        escribirArchivo("Archivos/entradaK", Cadena);
    }

}
int establecerConexionSubRoot(int cant_clientes_MOSIX, int Socket_Servidor, int* clientes, char** ips, char** datos) {
    int Socket_Cliente = -1, n = 0, id, r = 1;
    char* Cadena = calloc(50, sizeof (char));
    char* listo=calloc(100, sizeof (char));
    char* ip = calloc(15, sizeof (char));
    if (!establecerConexionCliente(Socket_Servidor, &Socket_Cliente, ip))
        return r;
    recibirDatos(Socket_Cliente, Cadena);
    id = buscarID(ip, ips, cant_clientes_MOSIX);
    strcat(listo,ip);
    strcat(listo,"\t");
    strcat(listo,Cadena);
    datos[id] = listo;
    if (comprobarIP(id, clientes)) {
        clientes[id] = Socket_Cliente;
        n++;
        r = 0;
    } else {
        close(Socket_Cliente);
    }
    return r;

}
/****************MODIFICADO****************/
void realizarconexionesSubRoot(int cant_clientes, int Socket_Servidor, int* clientes, char** ips, char** datos, char* letra) {
    int  i;
    char resultado_local[2];
    char* resultado;
    char* Cadena= calloc(100, sizeof (char));
    char nombre[100]="Archivos/ResultadosSubRoot";
    float a,b;
    if(strcmp(letra,"K")==0){
        strcat(nombre,"Krasovskii");  
        ejecutarKrasovsky();
        leerResultado("Archivos/salidaK",resultado_local);
        resultado=ips[0];
        strcat(resultado,"\t");
        strcat(resultado,resultado_local);
        datos[0]=resultado;
    }
    else if(strcmp(letra,"M")==0){
        strcat(nombre,"GeneradorCargaMOSRUNSinMigracion.txt");
        ejecutarGeneradorSM();
        leerResultado("Archivos/salidaSM",resultado_local);
        resultado=ips[0];
        strcat(resultado,"\t");
        strcat(resultado,resultado_local);
        datos[0]=resultado;
    }
    else if(strcmp(letra,"C")==0){
        strcat(nombre,"GeneradorCargaMOSRUNConMigracion.txt");
        getValores(&a,&b);
        sprintf(resultado_local,"%f",b);
        resultado=ips[0];
        strcat(resultado,"\t");
        strcat(resultado,resultado_local);
        datos[0]=resultado;
    }
    else if(strcmp(letra,"G")==0){
        strcat(nombre,"CalculandoTiempoEjecucionPERF.txt");
    }
    
    
    
        printf("\n====Recolectando Resultados====\n");
        for (i = 1; i < cant_clientes; i++) {
            establecerConexionSubRoot(cant_clientes, Socket_Servidor, clientes, ips, datos);
        }
        printf("\n*********Resultados*********\n");
    if (!faltaIP(cant_clientes, clientes, ips)) {
        for (i = 0; i < cant_clientes; i++) {
            strcat(Cadena, datos[i]);
            strcat(Cadena, "\n");
            printf("%s \n",datos[i]);
        }
        escribirArchivo(nombre, Cadena);
    }
    
}

/****************MODIFICADO****************/
void explorarRecursos(char** datos, int cant_clientes_MOSIX, int Socket_Servidor, int* clientes, char** ips) {
    clock_t tir, tfr;
    float dr;
    printf("\nExplorando recursos de esta maquina...\n");
    tir = time(0);
    datos[0] = obtenerRecursos(clientes[0]);
    tfr = time(0);
    dr = difftime(tfr, tir);
    printf("\nTiempo de descubrimiento de los recursos en este nodo: %.2f seg\n", dr);
    realizarconexiones(cant_clientes_MOSIX, Socket_Servidor, clientes, ips, datos);
}

/****************MODIFICADO****************/
void ejecutarKrasovsky() {
    clock_t t0, tf;
    float d;
    printf("\nAnalizando la estabilidad del cluster...\n");
    t0 = time(0);
    system("./krasovsky");
    tf = time(0);
    d = difftime(tf, t0);
    printf("Tiempo de analisis: %.2f seg\n\n", d);
}

/****************MODIFICADO****************/
void iniciarExperimento(char** datos, int cant_clientes_MOSIX, int Socket_Servidor, int* clientes, char** ips) {
    clock_t t0, tf; //,tir,tfr;
    char Cadena[10];
    float d; //,dr;
    t0 = time(0);
    init(clientes);
    clientes[0] = Socket_Servidor;
    cant_clientes_MOSIX = leerIps("Archivos/ips.txt", ips);
    explorarRecursos(datos, cant_clientes_MOSIX, Socket_Servidor, clientes, ips);
    ejecutarKrasovsky();
    tf = time(0);
    d = difftime(tf, t0);
    sprintf(Cadena, "%.2f", d);
    escribirArchivo("Archivos/TiempoTotal", Cadena);
    printf("\nTiempo total de ejecucion: %.2f seg\n\n", d);
}

/****************MODIFICADO****************/
void ejecutarGeneradorSM() {
    clock_t t0, tf;
    float d;
    char Cadena[10];
    t0 = time(0);
    printf("\nEjecutando generador de carga...\n");
    system("mosrun -L ./generador");
    tf = time(0);
    d = difftime(tf, t0);
    sprintf(Cadena, "%.2f", d);
    escribirArchivo("Archivos/salidaSM", Cadena);
    printf("\nTiempo total de ejecucion del MOSRUN sin migracion automatica: %.2f seg\n", d);
}

/****************MODIFICADO****************/
void ejecutarGeneradorCM() {
    clock_t t0, tf;
    float d;
    char Cadena[10];
    t0 = time(0);
    printf("\nEjecutando generador de carga...\n");
    system("mosrun ./generador");
    tf = time(0);
    d = difftime(tf, t0);
    sprintf(Cadena, "%.2f", d);
    escribirArchivo("Archivos/salidaCM", Cadena);
    printf("\nTiempo total de ejecucion del MOSRUN con migracion automatica: %.2f seg\n", d);
}

/****************MODIFICADO****************/
void DieWithError(char *errorMessage)  /* External error handling function */
{
    puts(errorMessage);
}

/****************MODIFICADO****************/
void brodcastServidor(int cantidad_ips, char** ips, char* sendString){
    int sock;                        
    struct sockaddr_in broadcastAddr; 
    unsigned short broadcastPort;     
                                     
    int broadcastPermission;          
    unsigned int sendStringLen;       
    broadcastPort= 20333;
    int i;
    for(i=1; i<cantidad_ips;i++){
        fprintf(stderr,"\nconectando con: %s",ips[i]);
        /* Create socket for sending/receiving datagrams */
        if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
            DieWithError("socket() failed");

        /* Set socket to allow broadcast */
        broadcastPermission = 1;
        if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, 
              sizeof(broadcastPermission)) < 0)
            DieWithError("setsockopt() failed");

        /* Construct local address structure */
        memset(&broadcastAddr, 0, sizeof(broadcastAddr)); 
        broadcastAddr.sin_family = AF_INET;                 
        broadcastAddr.sin_addr.s_addr = inet_addr(ips[i]);
        broadcastAddr.sin_port = htons(broadcastPort);
        sendStringLen = strlen(sendString);  
        if(sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
                DieWithError("sendto() sent a different number of bytes than expected");
        sleep(3);   
    }
}

/*Esta funcion permite la ejecucion simultanea del proceso broadcastServidor y el iniciarExperimento*/
int procesosDespertarCYRecolectar(int cantidad_ips, char** ips, char* sendString, char** datos, int cant_clientes_MOSIX, int Socket_Servidor, int* clientes ){
    //Creacion de proceso 
    int estado;
    pid_t pid = fork();
    if (pid == 0)
    {
        //sleep permite esperar a que se active la recoleccion primero
        sleep(3);
        printf("\nActivando recolección de recurso en los clientes ...\n");
        brodcastServidor(cantidad_ips, ips, sendString);
        printf("\r\nfinalizo el proceso de activación.");
        exit(33);//Sale del proceso hijo.
    }
    else if (pid > 0)
    {
        printf("\nRecolectando Recursos ...");
        iniciarExperimento(datos, cant_clientes_MOSIX, Socket_Servidor, clientes, ips); // ver bien las ips subroot y ips clientes
        wait(estado); //Espera al proceso hijo para que no quede huerfano.
    }
    else
    {
        printf("No se pudo crear proceso \n");
        return 1;
    }
    return 0;
    //Fin De proceso
}

/****************MODIFICADO****************/
main(int argc, char *argv[]) {
    /*
     * Descriptores de socket servidor y de socket con el cliente
     */
    system("clear");
    float  a, b;
    int canIpsDeSubRoots;
    char resultado_archivo[2]=""; 
    char *ips[MAX_IPS]; 
    char *ipsSubRoot[MAX_IPS];
    char* datos[MAX_IPS];
    int canIps; 
    int opcion=0, salir = 0;
    int Socket_Servidor = -1;           
    int  cant_clientes_MOSIX;
    int clientes[MAX_IPS];
    
    establecerConexionServidor(&Socket_Servidor);
    // arranco el root
     if(argc == 1){     
        //Cantidad de IPs de los SubRoot
              
        salir=0;
        do {
            switch (menu()) {
                case 1: 
                    system("./configcluster");
                    break;
                case 2:
                    canIpsDeSubRoots=leerIps("Archivos/ipsDeSubRoots.txt",ipsSubRoot);
                    canIps=leerIps("Archivos/ips.txt",ips); 
                    //Despierta los SubRoots.
                    printf("\nActivando recolección de recursos en los sub-roots:"),
                    brodcastServidor(canIpsDeSubRoots,ipsSubRoot,"S");
                    printf("\nComunicación de inicio finaliza.");
                    
                    //Despierta los clientes del root.
                    printf("\nRecolectando recursos de clientes ...");
                    procesosDespertarCYRecolectar(canIps, ips, "E", datos, cant_clientes_MOSIX, Socket_Servidor, clientes);
                    //Espera a que termine de despertarse los clientes antes de imprimir para que se vea bien el texto.
                    sleep(3*canIps);
                    printf("====Recoleccion En Root Finalizada====\n\n");
                    opcion=1;
                    break;
                    
                case 3:
                    system("vi readme.txt");
                    break;
                case 4:
                    salir = 1;
                    break;
            }

        } while (salir != 1);
       while (opcion == 1){
                    switch (menu1()) {
                        case 1:
                            brodcastServidor(canIpsDeSubRoots,ipsSubRoot,"K");
                            canIps=leerIps("Archivos/ipsDeSubRoots.txt",ips);
                            printf("Estabilidad del cluster utilizando el metodo de Krasovskii\n");
                            realizarconexionesSubRoot(canIps, Socket_Servidor, clientes, ips, datos,"K");
                            printf("verifique los resultados en Archivos/ResultadosSubRootKrasovskii\n ");
                            break;
                        case 2:
                            brodcastServidor(canIpsDeSubRoots,ipsSubRoot,"M");
                            canIps=leerIps("Archivos/ipsDeSubRoots.txt",ips);
                            printf("generador de carga con MOSRUN sin migracion automatica (mosix)\n");
                            realizarconexionesSubRoot(canIps, Socket_Servidor, clientes, ips, datos,"M");
                            printf("verifique los resultados en Archivos/ResultadosSubRootGeneradorCargaMOSRUNSinMigracion\n");
                            break;
                        case 3:
                            brodcastServidor(canIpsDeSubRoots,ipsSubRoot,"C");
                            canIps=leerIps("Archivos/ipsDeSubRoots.txt",ips);
                            printf("generador de carga con MOSRUN con migracion automatica (mosix)\n");
                            realizarconexionesSubRoot(canIps, Socket_Servidor, clientes, ips, datos,"C");
                            printf("verifique los resultados en Archivos/ResultadosSubRootGeneradorCargaMOSRUNConMigracion\n");
                            break;
                        case 4:
                            brodcastServidor(canIpsDeSubRoots,ipsSubRoot,"G");
                            canIps=leerIps("Archivos/ipsDeSubRoots.txt",ips);
                            printf("Calculando el tiempo de ejecucion de la carga (perf)\n");
                            realizarconexionesSubRoot(canIps, Socket_Servidor, clientes, ips, datos,"G");
                            printf("verifique los resultados en Archivos/ResultadosSubRootCalculandoTiempoEjecucionPERF");
                            break;
                        case 5:
                            // FinalizarConexionClientes(clientes, cant_clientes_MOSIX);
                            // close(Socket_Servidor);
                            opcion=2;
                            break;
                    }

                }
            }
    
            //Procesos del SubRoot
            else if (argc == 2 ) {  
                if(strcmp(argv[1],"S")== 0){
                    printf("====En Modo SubRoot====\n");
                    procesosDespertarCYRecolectar(canIps, ips, "E", datos, cant_clientes_MOSIX, Socket_Servidor, clientes);
                    close(Socket_Servidor);
                    Socket_Servidor = -1;
                    exit(0);
                }
                else if(strcmp(argv[1],"K")== 0){
                    close(Socket_Servidor);
                    Socket_Servidor = -1;
                    printf("\nEstabilidad del cluster utilizando el metodo de Krasovskii en sub root");
                    ejecutarKrasovsky();
                    leerResultado("Archivos/salidaK",resultado_archivo);
                    establecerConexionRoot(&Socket_Servidor,ips[0]);
                    enviarDatos(Socket_Servidor,resultado_archivo);  
                    exit(0);
                }
                else if(strcmp(argv[1],"M")==0){
                    close(Socket_Servidor);
                    Socket_Servidor = -1;
                    printf("\nEjecutando generador de carga con MOSRUN sin migracion automatica (mosix) en sub root");
                    ejecutarGeneradorSM();
                    leerResultado("Archivos/salidaSM",resultado_archivo);
                    establecerConexionRoot(&Socket_Servidor,ips[0]);
                    enviarDatos(Socket_Servidor,resultado_archivo);
                    exit(0); 
                }
                else if(strcmp(argv[1],"C")==0){
                    close(Socket_Servidor);
                    Socket_Servidor = -1;
                    printf("\nEjecutando generador de carga con MOSRUN con migracion automatica (mosix) en sub root");
                    ejecutarGeneradorCM();
                    leerResultado("Archivos/salidaCM",resultado_archivo);
                    establecerConexionRoot(&Socket_Servidor,ips[0]);
                    enviarDatos(Socket_Servidor,resultado_archivo);
                    exit(0);
                }
                else if(strcmp(argv[1],"G")==0){
                    close(Socket_Servidor);
                    Socket_Servidor = -1;
                    printf("\n Calculando el tiempo de ejecucion de la carga (perf) en sub root");
                    getValores(&a, &b);
                    printf("\nEl tiempo de ejecucion de la carga es: %.2f seg\n\n", b);
                    sprintf(resultado_archivo, "%f", b);
                    establecerConexionRoot(&Socket_Servidor,ips[0]);
                    enviarDatos(Socket_Servidor,resultado_archivo);
                    exit(0); 
                }
                else if(strcmp(argv[1],"help")==0) {
                printf("\nOpciones de ejecucion");
                printf("\n \t\t Activacion de la maquina como root");
                printf("\n S\t\t Activacion de recoleccion en sub-root");
                printf("\n K\t\t Ejecucion de evaluacion Krasovskii como sub-root");
                printf("\n M\t\t Generador de carga con MOSRUN sin migracion automatica (mosix) en sub root");
                printf("\n C\t\t Generador de carga con MOSRUN con migracion automatica (mosix) en sub root");
                printf("\n G\t\t Tiempo de ejecucion de la carga (perf) en sub root\n");

                exit(0);
               
            }
            }
            
            
            else{
                fprintf(stderr,"Use: %s <>\n", argv[0]);
                fprintf(stderr,"Use: %s <sub> \n", argv[0]);
                exit(0);
               
            }
         exit(0);  
}
