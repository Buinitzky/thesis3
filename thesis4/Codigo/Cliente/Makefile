all : Archivo.o Extras.o Comunicacion.o Socket.o Socket_Cliente.o Recursos.o Cliente

CPPFLAGS = -g -I.

Cliente : Cliente.c
	cc -g -I. Archivo.o Extras.o Comunicacion.o Socket.o Socket_Cliente.o Recursos.o Cliente.c -o Cliente

clean :
	rm *.o Cliente
