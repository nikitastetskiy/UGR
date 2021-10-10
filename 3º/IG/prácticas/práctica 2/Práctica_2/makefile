.PHONY: x clean tar

EJECUTABLE= practica_objetos_B2

MODULOS:= practica_objetos_B2.o\
         objetos_B2.o\
         file_ply_stl.o\

## MODIFICADO POR NIKITA STETSKIY PARA QUE GLUT FUNCIONE DE MANERA CORRECTA EN CADA SISTEMA OPERATIVO MAC/LINUX

LIBS			:=
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
		LDFLAGS += -lglut -lGLU -lGL -lsupc++ -lm -lc -lstdc++ -lpthread -L/usr/lib/nvidia-331
endif
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -framework GLUT -framework OpenGL -framework Cocoa
endif
      
CPPFLAGS:= -Wall -fmax-errors=2 -g

CC= g++

x: $(EJECUTABLE)
	./$(EJECUTABLE) beethoven

$(EJECUTABLE): $(MODULOS)	
	$(CC) -o $(EJECUTABLE) $(LDFLAGS) $(MODULOS) $(LIBS) 

clean:
	rm -rf *.o $(EJECUTABLE)