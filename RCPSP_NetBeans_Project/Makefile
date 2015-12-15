<<<<<<< HEAD
SYSTEM     =  x86-64_osx
LIBFORMAT  = static_pic
CPLEXDIR   = ./lib/cplex
CONCERTDIR =  ./lib/concert
=======
SYSTEM     = x86-64_sles10_4.1
LIBFORMAT  = static_pic


CPLEXDIR      = /opt/local/CPLEX_Studio/cplex/
CONCERTDIR    = /opt/local/CPLEX_Studio/concert/

>>>>>>> 6efde594899b3c4d73f3501a7b72f10cd66c7dde

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(SYSTEM)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

<<<<<<< HEAD
CPLEXFLAGS = -stdlib=libstdc++ -I$(CPLEXDIR)/include   -I$(CONCERTDIR)/include -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -lm -m64 -lpthread
CC = g++ -O0
CFLAGS = -std=c++11 -O2 -Wall -ansi -pedantic -DIL_STD
DEBUG = -pg -g -Wall -pedantic -DIL_STD
OBJECTS = parser.o flow.o main.o 

=======

CPLEXFLAGS    =  -I$(CPLEXDIR)/include   -I$(CONCERTDIR)/include -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -lm -m64 -lpthread


CC      = g++ -O0
CFLAGS  = -O2 -Wall -ansi -pedantic -DIL_STD
DEBUG   = -pg -g -Wall -ansi -pedantic -DIL_STD
OBJECTS = Parser.o Flow.o main.o 
>>>>>>> 6efde594899b3c4d73f3501a7b72f10cd66c7dde



exec : $(OBJECTS)
	$(CC) $(CFLAGS) -o exe $(OBJECTS) $(CPLEXFLAGS)
main.o : main.cpp 
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c main.cpp 
<<<<<<< HEAD
parser.o : parser.cpp parser.h
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c parser.cpp 	
flow.o : flow.cpp flow.h
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c flow.cpp 	
=======
Parser.o : Parser.cpp Parser.h
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c Parser.cpp 	
Flow.o : Flow.cpp Flow.h
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c Flow.cpp 	
>>>>>>> 6efde594899b3c4d73f3501a7b72f10cd66c7dde

clean :
	rm -f $(OBJECTS) exe
