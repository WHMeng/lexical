obj = main.o Fibonacci.o Triangular.o num_sequence.o

a : $(obj)
	g++ -o a $(obj)
main.o : main.cpp num_sequence.h Fibonacci.h
	g++ -Wall -c main.cpp -g
Fibonacci.o : Fibonacci.cpp Fibonacci.h
	g++ -Wall -c Fibonacci.cpp -g
Triangular.o : Triangular.cpp Triangular.h
	g++ -Wall -c Triangular.cpp -g
num_sequence.o : num_sequence.cpp num_sequence.h
	g++ -Wall -c num_sequence.cpp -g
.PHONY : clean
clean : 
	rm a $(obj)
