all : Extras.o Comunicacion.o Archivo.o Socket.o Socket_Servidor.o Socket_Cliente.o Recursos.o Socket_UDP_Cliente.o Servidor 

CPPFLAGS = -g -I.

Servidor : Servidor.c
	cc -g -I. Extras.o Comunicacion.o Archivo.o Socket.o Socket_Servidor.o Socket_Cliente.o Recursos.o Socket_UDP_Cliente.o Servidor.c -o Servidor 

clean :
	rm *.o Servidor
