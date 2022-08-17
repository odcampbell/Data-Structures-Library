# Data-Structures-Library

When compiling with test files given by TA's
(Phase1MainTest.cpp or Phase2Main.cpp), dont forget the
command line argument for which test to run!

There are 6 tests for each phase that you can run and theyre chosen via command line arguments.
If you forget the extra # (1-6) the program will not run successfully.

( We had to use a make file so the compilation is easy. After downloading the code and moving to the appropriate directory path
in your terminal, just type "make" into your terminal. )

e.g. 

make

Phase1 1

or 

make

Phase2 6

Also included in each directory is a more basic test main that might be easier to alter. Each of them should run by just altering the makefile 
to run them instead of the ones listed at the top of this readME.

e.g.

all: 
	g++ Phase1Main.cpp -std=c++11  -o Phase1 
