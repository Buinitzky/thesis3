
Para realizar la instalación de programa se deben realzar los siguientes pasos

0. Pre-requisitos

Se necesitan que esten instalados las dependencias del proyecto 
servidor anterior necesarios para su funcionamiento.

Armar el cluster, configurar el mosix en los nodos del cluster, para
la ejecución del programa es necesario que el archivo mosix.map tenga
todos los ips del cluster.

1. Configurar directorios de archivos

La carpeta del proyecto está dividida de la siguiente forma

\Proyecto
____Código/
__________todos los archivos fuente

____Install/
__________scrip.sh
__________servers.d
__________perf_instalacion/
__________service/
_______________init.d

____ProyectoFinal/
__________Archivos/
__________ejecutables y archivos necesarios.

Para la ejecución del programa son necesario que los directorios 
Install y ProyectoFinal esten en el mismo directorio.

/Carpeta contenedora/.
___/Install/
___/ProyectoFinal/


Todos los nodos del cluster deben contener las capetas del archivo.
La carpeta código no es neceria.

2. Instalación 

En la carpeta install/ se encuentra el scrip.sh este debe ser
ejecutado en todos los nodos este script instala los servicios necesarios para el funcionamiento de la evaluación.

se instalan 2 servios llamados server y configcluster que se ejecutan
en cada inicio del sistema.

nota: En caso de uqe en el computador no se encuentre instalado el perf o alguna de sus dependencias se debe ejecutar el archivo
install-perf-lips.sh que se encuentra en la ruta 
install/perf_instalacion/


····································································
el programa.

para ejecutar 

~$ubicación/#./Servidor

################################
1.Configurar cluster
2.Iniciar descubrimiento de recursos
3.ayuda
4.salir
opc:_
####################################
....................................................................
1.Configurar cluster
???????????????????????

La opción 1 es el módulo de configuración del cluster, aquí se puede modificar la división lógica del cluster.

###############################################
1.Cargar cluster desde moxis.map
2.Modificar tamaño de grupos y recargar cluster
9.salir
opc:_
###############################################

El proceso de configuración del cluster divide lógicamente los ips que se encuentran en el mosix.map utilizando el número máximo de nodos por grupo que por defecto es 6. Toma como nodo root el primer
ip que se encuentra en el mosix.map

La opción 1 configura el cluster con el último tamaño utilizado para configurar.

La opción 2 configura el cluster pero primero solicito el nuevo número de nodos de cada grupo.

:.................................................................
2.Iniciar descubrimiento de recursos
======================================

permite realizar la evaluación en el cluster.

Genera un nuevo menú que mustra las siguientes opciones.


:.................................................................
4 . salir

si no realizo la opción 2 se saldra del sistema, de lo contrario encontrará un segundo nivel de menu en donde se mostrarán las opciones contenidas en el proyecto anterior pero las operaciones 
se realizaran utilizando el nuevo programa. 

Despues de ejecutar cualquiera de los procesos anteriores se 
generará un reporte que se mostrará por pantalla y se generará un
archivo de resultado correspondiente a la opcion que ejecuto y
se encontrará en el dirrectorio  /ProyectoFinal/Archivos.



Para salir del editor que muestra la ayuda presione :q luego enter.



