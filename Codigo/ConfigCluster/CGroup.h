/* 
 * File:   CGroup.h
 * Author: Pedro Guarimata
 *
 * Created on 30 de enero de 2015, 08:53 PM
 */

#ifndef CGROUP_H
#define	CGROUP_H

#include "SimpleList.h"


#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct CGroup {
        /**
         * contiene el ip del nodo padre al cual enviará la respuesta de
         * estavilidad.
         */
        char *parent_ip;
        /**
         * ip contiene la dirección del nodo sub-root que controla el grupo.
         */
        char *ip;

        /**
         * indica si el grupo es estable o no
         */
        int stable;

        /**
         * si el nodo sub-root "host" fue configurado con la información
         * manejada en el cluster, es decir, si se fijaron los ips y las 
         * funciones que debe realizar.
         */
        int conf_set;

        /**
         contiene los ips de los integrantes del grupo
         */
        SimpleList *nodos;

    } CGroup;

    CGroup *createGroup(char *ip, SimpleList *nodos);

    /**
     * Mustra por la salida estandar la información del grupo.
     * @param item grupo a mosrar.
     */
    void showCGroup(CGroup *item);

    /**
     * Almacena la información del grupo en el stream.
     * @param group grupo que contiene la información.
     * @param file stream donde se envia la información del grupo.
     * @return 
     */
    void fputCGroupStream(CGroup *group, FILE *file);
    
    /**
     * Igual que fputCGroupStream pero solo almacena los 
     * ips contenido en la estructura sin información adicional.
     * @param group
     * @param file
     */
    void fputCGroupIpsStream(CGroup *group, FILE *file);
    
    /**
     * Lee desdes el Stream la información del grupo.
     * @param file flujo de archivo desde donde se leerá el grupo.
     * @return apuntador al struct CGroup si se leyo el grupo, NULL de lo
     * contrario.
     */
    CGroup *fgetCGroupStream(FILE *file);
    
    /**
     * Lee el stream y crea un grupo a partir de los ips en 
     * el stream leera size_group+1 elemento ya que el primer
     * ip que encuentre lo toma cómo el padre de grupo,
     * El segundo ip es el del sub-root y a partir de allí
     * lee size_group-1 ips del archivo.
     * @param file stream de donde se leerán los datos.
     * @param size_group tamaño de nodos en los grupos.
     * @return CGroup estructure con los ips leidos.
     */
    CGroup *fgetCGroupIpsStream(FILE *file, int size_group);
    
    /**
     * Almacena los datos del CGroup en el archivo indicado por el nombre.
     * @param group grupo que se almacenará
     * @param file_name archivo donde se escribirán los datos del 
     * archivo.
     * @return 1 si se almacena correctamente 0 si ocurre algún error.
     */
    int saveCGroupFile(CGroup *group, const char *file_name);
    
    /**
     * Almacena los ips padre e hijos de CGroup en el archivo indicado
     * @param group grupo con los ips.
     * @param file_name nombre del archivo..
     * @return 1 si se almacena correctamente 0 si no.
     */
    int saveCGroupIpsFile(CGroup *group, const char *file_name);
    
    /**
     * Lee la información del grupo desde el archivo indicado.
     * @param file_name nombre del arhivo indicado.
     * @return apuntador a la struct CGroup si se leyo el grupo, NULL de lo
     * contrario.
     */
    CGroup *readCGroupFile(const char *file_name);
    
    
#ifdef	__cplusplus
    }
#endif

#endif	/* CGROUP_H */

