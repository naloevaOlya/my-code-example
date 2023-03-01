CC=g++ -std=c++17 -g
BD=./
TESTS=tests/
CFLAGS=-c
LCOVFLAGS=-fprofile-arcs -ftest-coverage
GTESTFLAGS=-lgtest

all: clean main_test run_test

/$(BD)%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

./$(BD)%.o: $(TESTS)%.cpp
	$(CC) $(CFLAGS) $< -o $@

test: $(BD)main_test
	./$^

./$(BD)main_test: $(BD)main_test.o
	$(CC) $^ -o $@ $(GTESTFLAGS)

run_test:
	./main_test

cppcheck:
	cppcheck --enable=all --suppress=negativeIndex --suppress=uninitMemberVar --suppress=operatorEqVarError --suppress=noCopyConstructor --suppress=noOperatorEq --suppress=noExplicitConstructor --suppress=useStlAlgorithm --suppress=missingIncludeSystem ../src/

cpplint:
	cp ../materials/linters/CPPLINT.cfg . && python3 ../materials/linters/cpplint.py --extensions=cpp *.hpp
	python3 ../materials/linters/cpplint.py --extensions=cpp tests/*.cpp

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all -v --log-file=valgrind-out.txt ./main_test

leaks:
	leaks -atExit -- test

clean:
	rm -rf *.o *.a *.out *.dSYM *_exe test main_test
	rm -rf *.gcno *.gcda *.info report/
