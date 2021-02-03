# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= practica1_B

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraciÛn
#
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I.
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#

## MODIFICADO POR NIKITA STETSKIY PARA QUE GLUT FUNCIONE DE MANERA CORRECTA EN CADA SISTEMA OPERATIVO MAC/LINUX

LDFLAGS			:=
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
		LDFLAGS += -lGL -lGLU -lglut -lm
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -framework GLUT -framework OpenGL -framework Cocoa
endif

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
default : $(TARGETS)

# regla de ejecucion
#
$(TARGETS) : objetos_B.o practica1_B.o
	$(CC) -o $@ $(CXXFLAGS) objetos_B.o practica1_B.o $(LDFLAGS)

#
#
clean:
	rm -f *.o
	rm -f $(TARGETS)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)

#
#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGETS)
	tar -zcvf $(TARGETS).tgz *