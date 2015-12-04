SYSTEM     =  x86-64_osx
LIBFORMAT  = static_pic
CPLEXDIR   = ./lib/cplex
CONCERTDIR = ./lib/concert

CPLEXBINDIR   = $(CPLEXDIR)/bin/$(SYSTEM)
CPLEXLIBDIR   = $(CPLEXDIR)/lib/$(SYSTEM)/$(LIBFORMAT)
CONCERTLIBDIR = $(CONCERTDIR)/lib/$(SYSTEM)/$(LIBFORMAT)

CPLEXFLAGS = -stdlib=libstdc++ -I$(CPLEXDIR)/include   -I$(CONCERTDIR)/include -L$(CPLEXLIBDIR) -lilocplex -lcplex -L$(CONCERTLIBDIR) -lconcert -lm -m64 -lpthread
CC = g++
CFLAGS = -std=c++11 -O2 -Wall -ansi -pedantic -DIL_STD
DEBUG = -pg -g -Wall -ansi -pedantic -DIL_STD
OBJECTS= first_prog.o

exec : $(OBJECTS)
	$(CC) $(CFLAGS) -o exe $(OBJECTS) $(CPLEXFLAGS)
.cpp.o :
	$(CC) $(CFLAGS) $(CPLEXFLAGS) -c $< -o $@
clean :
	rm -f $(OBJECTS) exe
