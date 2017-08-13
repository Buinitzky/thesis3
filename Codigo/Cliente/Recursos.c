
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//#include <errno.h>
#include<linux/wireless.h>
#include<Extras.h>

#include "Recursos.h"
#include "Archivo.h"

#define maxcmd 4
#define MB 1048576



float getVmWifi(char* ethname){
   struct iwreq req;
   strcpy(req.ifr_name, ethname);
   
   struct iw_statistics *stats;
   int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) 
    {
        fprintf(stdout,"Cannot get control socket");
        return -1;
    }

   req.u.data.pointer=(struct iw_statistics *)malloc(sizeof(struct iw_statistics));
   req.u.data.length=sizeof(struct iw_statistics);
   int a;
   if((ioctl(fd, SIOCGIWRATE, &req))!=-1){
       memcpy(&a,&req.u.bitrate,sizeof(int));
       return a;
   }
}




float GetVm(unsigned char *ethname)
{
    float a=0;
    switch(ethname[0]){
        case 'e':
            a=getVmCable(getName())/8;
            
            break;
        case 'w':
            a=getVmWifi(ethname)/(8.0*1024.0*1024.0);
            break;
        default:
            printf("\nError Interfaz de red no reconocida.\n");
            exit(-1);
    }
    return a;
}
 
char* obtenerRecursos(){
    char* cad=calloc(100,sizeof(char));
    char cmd[maxcmd][100];
    char nbFile[30];
    float datos[5];
    float trabajo_MB;
    float Vc=0,TTC=0,Vm,memoria,Ve,tc=1,te;
    int i;
    
    leerArchivo("Archivos/entradaG",datos);
    trabajo_MB=datos[1];
    if(datos[0]==1){
        TTC=1/trabajo_MB;
        Vc=trabajo_MB/tc;
    }
    
    Vm=GetVm(getName());
    
    strcpy(cmd[0], "grep 'MemTotal' /proc/meminfo |grep -ioE '[0-9]+' > recursos.txt");
    strcpy(cmd[1], "perf stat -o stress.tmp ./carga");
    strcpy(cmd[2], "sed 's/\\,/\\./g' stress.tmp| cat> stress2.tmp");
    strcpy(cmd[3], "cat stress2.tmp |grep 'seconds time elapsed'| grep -ioE '[0-9]+\\.[0-9]{2}' >> recursos.txt");
    strcpy(nbFile,"recursos.txt");
    
    for( i=0; i<maxcmd;i++){
        system(cmd[i]);
    }
    /*system("rm stress.tmp");
    system("rm stress2.tmp");*/
    
    
     FILE* archivo;
    char linea[10];
    archivo=fopen(nbFile,"r");
    float recursos[2];
    for(i=0;fgets(linea,10,archivo)!=NULL;i++){
       recursos[i]=atof(linea); 
    }
    recursos[0]/=1024;
    if(!fclose(archivo)==0)
       printf("Error al cerrar archivo: %s",nbFile);
    memoria=recursos[0];
    te=recursos[1];
    
    Ve=trabajo_MB/te;
    
    sprintf(cad, "%.2f %.2f %.2f %.2f %.2f", Vc, TTC, Vm,memoria,Ve);  
 
    return cad;
}