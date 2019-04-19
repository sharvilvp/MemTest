
all : march 
	@./march

march : march_tests.o memory_struct.o coverage.o main.o
	g++ $(CLFAGS) -Wall -Wextra -Weffc++ -Wpedantic -Werror -pedantic-errors  -o march main.o coverage.o march_tests.o memory_struct.o -I.

#%.o : %.h %.cpp
#	g++ -o main.o  -I. -c main.cpp

memory_struct.o : 
	g++ $(CLFAGS) -o memory_struct.o -I. -c memory_struct.cpp

coverage.o :
	g++ $(CLFAGS) -o coverage.o -I. -c coverage.cpp

#test_parser.o :
#	g++ -o test_parser.o -I. -c test_parser.cpp	

main.o :
	g++ $(CLFAGS) -o main.o -I. -c main.cpp

march_tests.o :
	g++ $(CLFAGS) -o march_tests.o -I. -c march_tests.cpp

clean : 
	rm *.o 
