all : main

clean :
	rm main *.o

run : main
	./main

main : main.o Task.o Database.o load.o save.o
	g++ -std=c++17 $^ -lstdc++fs -o $@

%.o : %.cpp
	g++ -std=c++17 -c $<
