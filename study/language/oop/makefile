obj = main.o Fibonacci.o num_sequence.o

a : $(obj)
	g++ -o a $(obj) -g
main.o : Fibonacci.h num_sequence.h
	g++ -Wall -c main.cpp -g
Fibonacci.o : Fibonacci.h
	g++ -Wall -c Fibonacci.cpp -g
num_sequence.o : num_sequence.h
	g++ -Wall -c num_sequence.cpp -g
.PHONY : clean
clean :
	rm a $(obj)
