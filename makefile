compile: 
	g++ -std=c++14 -Wall -pedantic src/*.cpp -o gbw.out

valrun:
	valgrind ./gbw.out.out

clean:
	rm -f ./gbw.out
