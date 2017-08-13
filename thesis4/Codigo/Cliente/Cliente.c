
#include <stdio.h>
#include <Socket_Cliente.h>
#include <Socket.h>
#include <Comunicacion.h>
#include <string.h>
#include <stdlib.h>
#include <Extras.h>
#include "Archivo.h"
#define MAX_IPS 10

void establecerConexionServidor(int* Socket_Con_Servidor,char* Cadena){
    *Socket_Con_Servidor = Abre_Conexion_Inet (Cadena, "cpp_java");
	if (*Socket_Con_Servidor == -1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
		exit (-1);
	}
}
main ()
{

	int Socket_Con_Servidor;
	char* Cadena=calloc(100,sizeof(char));
        char* ips[MAX_IPS];
        int cant_ips= leerIps("Archivos/ips.txt",ips);
        if(cant_ips==1){
            printf("\nExplorando recursos de esta maquina ...\n");
            strcpy(Cadena,obtenerRecursos(Socket_Con_Servidor));
            establecerConexionServidor(&Socket_Con_Servidor,ips[0]);
            enviarDatos(Socket_Con_Servidor,Cadena);
            printf("\ndatos enviados con exito");
            
        }
        else{
            printf("Ocurrio un error inesperado");
        }
        
}
