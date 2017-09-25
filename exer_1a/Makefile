# compiler settings ------------------------------------------------------------

CC := gcc
CXX := g++
override CFLAGS += -std=c11 -Wall -g3
override CXXLAGS += -std=c++11 -Wall -g3

# location of user-installed libraries
LIBDIR := /usr/local/lib




#
.PHONY : all

# default rule
all : exer_1a utest_calc_bodies

clean :
	rm -f *.o

clobber :
	rm -f *.o exer_1a





# exercise build rules ---------------------------------------------------------

exer_1a.o : vec_2d.h

exer_1a : override LDLIBS += -lm
exer_1a : calc_bodies.o exer_1a.o

calc_bodies.o : vec_2d.h





# test build rules -------------------------------------------------------------


utest_calc_bodies : override LDFLAGS += -L$(LIBDIR)
utest_calc_bodies : override LDLIBS += -lcppunit
utest_calc_bodies : calc_bodies.o
