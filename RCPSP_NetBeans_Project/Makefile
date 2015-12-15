SYSTEM     =  x86-64_osx
LIBFORMAT  = static_pic
CPLEXDIR   = ./lib/cplex
CONCERTDIR =  ./lib/concert

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(SYSTEM)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CPLEXFLAGS = -stdlib=libstdc++ -I$(CPLEXDIR)/include   -I$(CONCERTDIR)/include -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -lm -m64 -lpthread
CC = g++ -O0
CFLAGS = -std=c++11 -O2 -Wall -ansi -pedantic -DIL_STD
DEBUG = -pg -g -Wall -pedantic -DIL_STD
OBJECTS = parser.o flow.o main.o 




exec : $(OBJECTS)
	$(CC) $(CFLAGS) -o exe $(OBJECTS) $(CPLEXFLAGS)
main.o : main.cpp 
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c main.cpp 
parser.o : parser.cpp parser.h
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c parser.cpp 	
flow.o : flow.cpp flow.h
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c flow.cpp 	

clean :
	rm -f $(OBJECTS) exe
