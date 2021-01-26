all: pqp

pqp: pqp.cpp entrada.o voo.o Fila.o FilaOrd.o Pistas.o itoa.o sorteio.o saferealloc.o
	g++ -g -o pqp pqp.cpp entrada.o voo.o Fila.o FilaOrd.o Pistas.o itoa.o sorteio.o saferealloc.o

saferealloc.o: saferealloc.cpp
	g++ -g -c saferealloc.cpp
voo.o: voo.cpp
	g++ -g -c voo.cpp
Fila.o: Fila.cpp
	g++ -g -c Fila.cpp
FilaOrd.o: FilaOrd.cpp
	g++ -g -lm -c FilaOrd.cpp
entrada.o: entrada.cpp
	g++ -g -c entrada.cpp
sorteio.o: sorteio.cpp
	g++ -g -c sorteio.cpp
itoa.o: itoa.cpp
	g++ -g -c itoa.cpp
Pistas.o: Pistas.cpp
	g++ -g -c Pistas.cpp

clean:
	rm -Rf *.o
