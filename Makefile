inicio:
	g++ -o exe ejemplo1.cpp
	./exe
	rm exe

hilos:
	g++ -o exe hilos.cpp -lpthread
	./exe
	rm exe