obj = main.o BinaryTree.o BTnode.o

a : $(obj)
	g++ -Wall -o a $(obj)
main.o : main.cpp BinaryTree.h
	g++ -Wall -c main.cpp -g
BinaryTree.o : BinaryTree.cpp BinaryTree.h
	g++ -Wall -c BinaryTree.cpp -g
BTnode.o : BTnode.cpp BTnode.h
	g++ -Wall -c BTnode.cpp -g
.PHONY : clean
clean :
	rm a $(obj)
