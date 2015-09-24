CXX = g++-4.8
CXXFLAGS = -pedantic --std=c++11 -Werror
TESTLIBS = -lgtest -lpthread -lgtest_main
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

clean:
	rm -f twobuttons
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f twobuttons.report

twobuttons: clean twobuttons.cpp
	$(CXX) $(CXXFLAGS) -o twobuttons twobuttons.cpp

buildtest: twobuttons.cpp
	$(CXX) $(CXXFLAGS)  $(GCOVFLAGS) -o twobuttons -DTESTING twobuttons.cpp $(TESTLIBS)

regress: clean buildtest
	./twobuttons

regress_report: regress
	$(VALGRIND) ./twobuttons
	$(GCOV) -b twobuttons.cpp | grep -A 5 "File 'twobuttons.cpp'" >> twobuttons.report
	cat twobuttons.report
