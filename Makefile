# Dependancies make with: ar rcs dependencies.a GeneralFunctions.o StringProcessing.o

output: main.o libdependencies.a
	g++ -std=c++17 -o output main.o -L. -ldependencies

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

clean:
	rm output main.o