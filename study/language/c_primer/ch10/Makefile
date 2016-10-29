obj = main.o TextQuery.o

tq : $(obj)
	g++ -o tq $(obj) -g
main.o : main.cpp TextQuery.h
	g++ -c -Wall main.cpp -g
TextQuery.o : TextQuery.cpp TextQuery.h
	g++ -c -Wall TextQuery.cpp -g
.PHONY : clean
clean :
	rm tq $(obj)
