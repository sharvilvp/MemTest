
all : march 
	@./march

march : march_tests.o memory_struct.o main.o
	g++ -Wall -Wextra -Weffc++ -Wpedantic -Werror -pedantic-errors  -o march main.o march_tests.o memory_struct.o -I.

#%.o : %.h %.cpp
#	g++ -o main.o  -I. -c main.cpp

memory_struct.o : 
	g++ -o memory_struct.o -I. -c memory_struct.cpp

#test_parser.o :
#	g++ -o test_parser.o -I. -c test_parser.cpp	

main.o :
	g++ -o main.o -I. -c main.cpp

march_tests.o :
	g++ -o march_tests.o -I. -c march_tests.cpp

clean : 
	rm *.o 
