INCLUDE=-Iinclude

all:bin/simulacion

bin/simulacion: obj/miniwin.o obj/simulacion.o obj/particula.o obj/Nubeparticula.o obj/Simulador.o
			g++ -o bin/simulacion obj/miniwin.o obj/simulacion.o obj/particula.o obj/Nubeparticula.o obj/Simulador.o -pthread -lX11 -std=c++11

obj/simulacion.o: include/miniwin.h src/main.cpp
			g++ -c -o obj/simulacion.o src/main.cpp $(INCLUDE) -std=c++11

obj/particula.o: src/particula.cpp include/particula.h include/miniwin.h
	g++ -c -o obj/particula.o src/particula.cpp $(INCLUDE)

obj/Nubeparticula.o: src/Nubeparticula.cpp include/particula.h include/Nubeparticula.h include/miniwin.h
	g++ -c -o obj/Nubeparticula.o src/Nubeparticula.cpp $(INCLUDE)

obj/Simulador.o: src/Simulador.cpp include/particula.h include/Nubeparticula.h include/Simulador.h include/miniwin.h
	g++ -c -o obj/Simulador.o src/Simulador.cpp $(INCLUDE)
 
obj/miniwin.o: src/miniwin.cpp include/miniwin.h
			g++ -c -o obj/miniwin.o src/miniwin.cpp $(INCLUDE) -std=c++11

clean:
	@echo "limpiando..."
	rm obj/*.o
	rm bin/simulacion
