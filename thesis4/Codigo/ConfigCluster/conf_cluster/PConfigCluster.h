/* 
 * File:   PConfigCluster.h
 * Author: Pedro Guarimata
 *
 * Created on 29 de enero de 2015, 06:03 PM
 */

#ifndef PCONFIGCLUSTER_H
#define	PCONFIGCLUSTER_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <unistd.h>
#include "PGFile.h"
#include "CGroup.h"

    /**
     * Contine la información relevante de la separacion lógica
     */
    typedef struct Cluster {
        char *root;
        int l;
        int npg;
        SimpleList *grupos;
        SimpleList *ips;
    } Cluster;
    
    /**
     * Crea y reserva la memoria para almacenar un struct Cluster vacio.
     */
    Cluster *createEmptyCluster();

    /**
     * Crea y reserva a partir de la lista de ips, la memoria para almacenar un struct Cluster.
     * @param npg número de nodos por grupo
     * @param ips ips que contiene el Cluster.
     * @return apuntador al struct cluster.
     */
    Cluster *createCluster(int npg, SimpleList *ips);

    /**
     * muestra por la salida estandar la información que contiene el cluster.
     * @param item
     */
    void showCluster(Cluster *item);

    /**
     * Almacena la información del cluster en el archivo indicado por file_name.
     * @param cluster cluster que se almacenará en el archivo.
     * @param file_name nombre del archivo que se almacenará.S
     * @return retorna 1 si el cluster fue almacenado correctamente 0 de lo
     * contrario.
     */
    int saveCluster(Cluster *cluster, const char *file_name);

    /**
     * Lee y carga los datos del cluster que se encuentra en el archivo indicado.
     * @param file_name nombre del archivo.
     * @return puntero struct cluster
     */
    Cluster *readClusterFile(const char *file_name);
    /**
     * inicializa el cluster desde el archivo mosix.map esto crea una dependencia
     * al programa por lo tanto este debe existir para que el programa funciones.
     * @param nodos_grupo indica el número de nodos que habra en cada grupo
     * incluyendo a los nodos sub_roots
     * @return Cluster* que contiene la información del cluster formado y los 
     * nodos de cada sub_grupo.
     */
    Cluster *initCluster(int nodos_grupo);

    /**
     * Busca en entre los grupos del cluster el grupo cuyo sub-root posea
     * el ip solicitado.
     * @param cluster cluster contenedor de la información.
     * @param ip ip que se solicita la cliente.
     * @return CGroup *.
     */
    CGroup *getGroupByIP(Cluster *cluster, char *ip);

#ifdef	__cplusplus
}
#endif

#endif	/* PCONFIGCLUSTER_H */

