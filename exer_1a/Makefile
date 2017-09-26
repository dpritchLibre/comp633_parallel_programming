# compiler settings ------------------------------------------------------------

CC := gcc
CXX := g++
override CFLAGS += -std=c11 -Wall -g3
override CXXFLAGS += -std=c++11 -Wall -g3

# location of user-installed libraries
LIBDIR := /usr/local/lib




# primary makefile targets -----------------------------------------------------

.PHONY : all clean clobber

# default rule
all : exer_1a utest_calc_bodies

clean :
	rm -f *.o

clobber :
	rm -f *.o exer_1a utest_calc_bodies




# exercise build rules ---------------------------------------------------------

calc_bodies_blk.o : calc_bodies.h vec_2d.h
calc_bodies_third_law.o : calc_bodies.h vec_2d.h

# the defines is used so that the `clock_gettime` function and macros are
# declared.  See https://stackoverflow.com/a/8881705/5518304
exer_1a.o : override CPPFLAGS += -D_POSIX_C_SOURCE=199309L
exer_1a.o : vec_2d.h

exer_1a : override LDLIBS += -lm
exer_1a : calc_bodies_blk.o calc_bodies_third_law.o exer_1a.o




# test build rules -------------------------------------------------------------

utest_calc_bodies : override LDFLAGS += -L$(LIBDIR)
utest_calc_bodies : override LDLIBS += -lcppunit
utest_calc_bodies : calc_bodies_blk.o calc_bodies_third_law.o
