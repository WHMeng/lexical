obj = main.o Fibonacci.o Triangular.o num_sequence.o

a : $(obj)
	g++ -o a $(obj)
main.o : num_sequence.h Fibonacci.h
	g++ -Wall -c main.cpp -g
Fibonacci.o : Fibonacci.h
	g++ -Wall -c Fibonacci.cpp -g
Triangular.o : Triangular.h
	g++ -Wall -c Triangular.cpp -g
num_sequence.o : num_sequence.h
	g++ -Wall -c num_sequence.cpp -g
.PHONY : clean
clean : 
	rm a $(obj)
