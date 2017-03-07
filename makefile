compile: 
	g++ -std=c++14 -Wall -pedantic src/*.cpp -o bw.out

valrun:
	valgrind ./bw.out

clean:
	rm -f ./bw.out
