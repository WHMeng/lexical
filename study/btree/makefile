obj = main.o BTnode.o BinaryTree.o

a : $(obj)
	g++ -Wall -o a $(obj)
main.o : BinaryTree.h
	g++ -Wall -c main.cpp -g
BinaryTree.o : BinaryTree.h
	g++ -Wall -c BinaryTree.cpp -g
BTnode.o : BTnode.h
	g++ -Wall -c BTnode.cpp -g
.PHONY : clean
clean :
	rm a $(obj)
