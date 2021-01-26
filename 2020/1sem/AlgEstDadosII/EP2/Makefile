
all: grafosT

grafosT: grafosT.cpp experimento.o grafo.o Fila.o ab.o EstrutTSO.o livro.o
	g++ -g -o grafosT grafosT.cpp livro.o EstrutTSO.o Fila.o ab.o grafo.o experimento.o 
experimento.o: experimento.cpp
	g++ -g -c experimento.cpp
grafo.o: grafo.cpp
	g++ -g -c grafo.cpp
Fila.o: Fila.cpp
	g++ -g -c Fila.cpp
ab.o: ab.cpp
	g++ -g -c ab.cpp
EstrutTSO.o: EstrutTSO.c
	g++ -g -c EstrutTSO.c
livro.o: livro.c
	g++ -g -c livro.c
clean:
	rm *.o
