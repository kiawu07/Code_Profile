CC = g++
CFLAGS = -Wall -std=c++14

main: main.o client.o account.o invest.o
	$(CC) $(CFLAGS) main.o client.o account.o invest.o -o main

main.o: main.cpp client.hpp account.hpp invest.hpp
	$(CC) $(CFLAGS) -c main.cpp

client.o: client.cpp client.hpp
	$(CC) $(CFLAGS) -c client.cpp

account.o: account.cpp account.hpp client.hpp
	$(CC) $(CFLAGS) -c account.cpp	

invest.o: invest.cpp invest.hpp account.hpp stock.hpp holding.hpp exceptions.hpp
	$(CC) $(CFLAGS) -c invest.cpp 

clean:
	rm *.o main