obj = main.o Triangular.o Triangular_iterator.o

a : $(obj)
	g++ -o a $(obj)
main.o : Triangular.h Triangular_iterator.h
	g++ -c -Wall main.cpp -g
Triangular.o : Triangular_iterator.h
	g++ -c -Wall Triangular.cpp -g
Triangular_iterator.o : Triangular.h
	g++ -c -Wall Triangular_iterator.cpp -g
.PHONY : clean
clean :
	rm a $(obj)
