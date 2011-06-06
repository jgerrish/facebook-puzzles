all: gattaca

gattaca: main.cpp prediction.cpp problem.cpp
	$(CXX) -g -o $@ $^

tests: test

test: tests/test.cpp prediction.cpp problem.cpp
	$(CXX) -I. -g -o $@ $^

clean:
	rm -f *.o
	rm -f gattaca
