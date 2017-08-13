#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int leerArchivoMOSIX(char* nombre_archivo,char** Cadena){
    //*Cadena="";
    FILE* archivo;
    char* ip;
    char aux[5];
    char nodos[5];
    int n=0;
    if(archivo=fopen(nombre_archivo,"r")){
        while(!feof(archivo)){
            
            ip=calloc(15,sizeof(char));
            fscanf(archivo," %s %s %s ", ip,nodos,aux);
            //printf("%s %s %s ",ip,nodos,aux);
            Cadena[n++]=ip;
        }
        if(!fclose(archivo)==0)
           printf("\nError al cerrar archivo: %s\n",nombre_archivo);
    }
    else
         printf("\nError al abrir archivo: %s\n",nombre_archivo);
    return n;

}

void leerArchivo(char* nombre_archivo, float* datos ){
    //*Cadena="";
    FILE* archivo;
    char* linea;
    int cont=0;
    linea=calloc(10,sizeof(char));
    archivo=fopen(nombre_archivo,"r");
    if(archivo){
        while(fgets(linea,10,archivo)!=NULL){
            datos[cont++]=atof(linea);
            linea=calloc(10,sizeof(char));
        }
        if(!fclose(archivo)==0)
           printf("\nError al cerrar archivo: %s\n",nombre_archivo);
    }
    else{
        printf("\nError al abrir archivo %s\n",nombre_archivo);
    }
    

}

void escribirArchivo(char* nombre_archivo,char* contenido){
    FILE* archivo=fopen(nombre_archivo,"w");
    fprintf(archivo,"%s",contenido);
    if(!archivo)
         printf("\nError al abrir archivo: %s\n",nombre_archivo);
    
    if(!fclose(archivo)==0){
        printf("\nError al cerrar archivo: %s\n",nombre_archivo);
    }
    printf("Datos guardados satisfactoriamente en %s\n",nombre_archivo);
    
}
int leerIps(char* nombre_archivo, char** ips)
{
    FILE* archivo;
    char* ip;
    int n=0;
    if(archivo=fopen(nombre_archivo,"r")){
        while(!feof(archivo)){
            
            ip=calloc(15,sizeof(char));
            fscanf(archivo," %s ", ip);
            ips[n++]=ip;
        }
        if(!fclose(archivo)==0)
           printf("\nError al cerrar archivo: %s\n",nombre_archivo);
    }
    else
         printf("\nError al abrir archivo: %s\n",nombre_archivo);
    return n;
}
void leerResultado(char* nombre,char* ips)
{
    
    FILE *archivo;
    archivo = fopen(nombre,"r");
    if (archivo == NULL){
	printf("\nError de apertura del archivo. \n\n");
    }else{
        while (feof(archivo) == 0)
	    {
		fgets(ips,100,archivo);
	    }
    }
    fclose(archivo);
}
void mostrarResultado(char* nombre, char* cadena)
{
    
    FILE *archivo;
    char buff[20];
    archivo = fopen(nombre,"a");
    if (archivo == NULL){
            printf("\nError de apertura del archivo. \n\n");
    }else{
        while (fgets(buff,20, archivo) != NULL)
        {
            cadena = strdup(buff);
            strcat(cadena,"\n");
        }
    }
    fclose(archivo); 
}