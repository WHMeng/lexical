obj = main.o

a : $(obj)
	g++ -Wall -o a $(obj)
main.o : main.cpp BinaryTree.h
	g++ -Wall -c main.cpp -g
.PHONY : clean
clean :
	rm a $(obj)
