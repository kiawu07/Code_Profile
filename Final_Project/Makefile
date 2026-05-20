CC = g++
CFLAGS = -Wall -std=c++14

final: node.o list.o finalpro.o user.o
	$(CC) $(CFLAGS) node.o user.o list.o finalpro.o -o final

finalpro.o: finalpro.cpp node.hpp list.hpp user.hpp
	$(CC) $(CFLAGS) -c finalpro.cpp

list.o: list.cpp node.hpp list.hpp
	$(CC) $(CFLAGS) -c list.cpp

user.o: user.cpp user.hpp
	$(CC) $(CFLAGS) -c user.cpp

node.o: node.cpp node.hpp
	$(CC) $(CFLAGS) -c node.cpp

clean:
	rm *.o final	