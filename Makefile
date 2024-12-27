FLAGS = -O3

all: main.o matrix.o value.o
	g++ main.o matrix.o value.o

main.o: main.cpp matrix.hpp value.hpp
	g++ main.cpp -c $(FLAGS) -o main.o

matrix.o: matrix.cpp matrix.hpp
	g++ matrix.cpp -c $(FLAGS) -o matrix.o

value.o: value.cpp value.hpp
	g++ value.cpp -c $(FLAGS) -o value.o

clean:
	rm -f *.o *out

zip:
	zip ex3.zip *.cpp *.hpp Makefile