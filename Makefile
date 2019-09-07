default: knn

knn.o: knn.cc
	g++ -O3 -c knn.cc -o knn.o

knn: knn.o
	g++ knn.o -o knn

clean:
	-rm -f knn.o
	-rm -f knn