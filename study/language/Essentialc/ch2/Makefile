obj = main.o NumSeq.o

a : $(obj)
	g++ -o -Wall $(obj)
NumSeq.o : NumSeq.cpp NumSeq.h
	g++ -c -Wall NumSeq.cpp
main.o : main.cpp NumSeq.h
	g++ -c -Wall main.cpp
.PHONY : clean
clean :
	rm a $(obj)
