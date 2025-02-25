

inicio:
	g++ -o exe ejemplo1.cpp
	./exe
	rm exe

hilos:
	g++ -o exe hilos.cpp -lpthread
	./exe
	rm exe

tbb:
	g++ -o exe hilostbb.cpp -ltbb
	./exe
	rm exe

all: inicio hilos tbb