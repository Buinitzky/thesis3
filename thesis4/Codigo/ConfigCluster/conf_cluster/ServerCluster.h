/* 
 * File:   ServerCluster.h
 * Author: Pedro Guarimata
 *
 * Es el servidor del cluster y coordina el funcionamiento de este.
 * se encarga de recibir las peticiones de los nodos hijos del nodo que instacia
 * el sevidor.
 * Created on 20 de febrero de 2015, 04:50 PM
 */

#ifndef SERVERCLUSTER_H
#define	SERVERCLUSTER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <bits/socket.h>
#include "PConfigCluster.h"
#define PORT_CONF 18001
#define PORT_STRM 18002
#define PACK_SIZE 512
#define SERV_UDP "conf-clustdgam"
#define SERV_TCP "conf-cluststrm"
    
    /**
     * Envia la vandera indicada a los ips que se encuentren en la lista
     * @param list que contiene los ips a comunicar.
     * @param flag indicador.
     * @return 0 si se realiza la operación, -1 en caso de error.
     */
    int sendFlagToIpsList(SimpleList *list, char *flag);
    
    /**
     * envia la vandera indicada a los sub-roots del cluster.
     * @param cluster cluster con la información.
     * @param service_name nombre del servicio a enviar.
     * @return 0 si se completo el envio a todos los sub-roots.
     */
    int initServiceSubRoots(Cluster *cluster, char *service_name);
    
    /**
     * Rutina ejecutada por el root para esperar la coneccion de los subroots y 
     * asignarles los ips de los grupos.
     * @param cluster que contiene la configuración.
     * @return -1 si error
     */
    int waitSubRootsRecall(Cluster *cluster);
    
    //sub-roots
    
    /**
     * Rutina para esperar ordenes del root queda esperando una orden en el
     * puerto 16700 luego la ejecuta y epera por otra orden.
     * @return -1 si error
     */
    int waitOrderFromRoot();
    
    /**
     * Rutina ejecutada por los subroots para realizar la petición de su 
     * configuración.
     * @param group
     * @param ip_root
     * @return 
     */
    CGroup *callRootForData(char *ip_root);
    
#ifdef	__cplusplus
}
#endif

#endif	/* SERVERCLUSTER_H */

