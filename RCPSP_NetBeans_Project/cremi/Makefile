SYSTEM     = x86-64_sles10_4.1
LIBFORMAT  = static_pic


CPLEXDIR      = /opt/local/CPLEX_Studio/cplex
CONCERTDIR    = /opt/local/CPLEX_Studio/concert


CPLEXBINDIR   = $(CPLEXDIR)/bin/$(SYSTEM)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)


CPLEXFLAGS    =  -I$(CPLEXDIR)/include   -I$(CONCERTDIR)/include -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -lm -m64 -lpthread


CC      = g++ -O0
CFLAGS  = -O2 -Wall -ansi -pedantic -DIL_STD
DEBUG   = -pg -g -Wall -ansi -pedantic -DIL_STD
OBJECTS = Parser.o Flow.o Time_indexed.o main.o 



exec : $(OBJECTS)
	$(CC) $(CFLAGS) -o exe $(OBJECTS) $(CPLEXFLAGS)
main.o : main.cpp 
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c main.cpp 
Parser.o : Parser.cpp Parser.h
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c Parser.cpp 	
Flow.o : Flow.cpp Flow.h
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c Flow.cpp 	

Time_indexed.o : Time_indexed.cpp Time_indexed.h
        $(CC) $(CFLAGS) $(CPLEXFLAGS) -c Time_indexed.cpp       



clean :
	rm -f $(OBJECTS) exe
