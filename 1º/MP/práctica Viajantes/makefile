INCLUDE= -Iinclude
all : tsp
tsp : obj/funciones.o obj/main.o
	g++ -o tsp obj/funciones.o obj/main.o
obj/main.o : src/main.cpp include/funciones.h
	g++ -c src/main.cpp $(INCLUDE) -o obj/main.o
obj/funciones.o : src/funciones.cpp include/funciones.h
	g++ -c src/funciones.cpp $(INCLUDE) -o obj/funciones.o
clean :
	echo "Limpiando..."
	rn obj/*.o
	rn tsp
