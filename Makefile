all: main.o data.o person.o
	g++ main.o data.o person.o -o Lab5
	
main.o: main.cpp
	g++ -c main.cpp
	
data.o: data.cpp
	g++ -c data.cpp
	
person.o: person.cpp
	g++ -c person.cpp
	
clean:
	rm -rf *.o