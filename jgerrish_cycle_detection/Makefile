all: jgerrish_cycle_detection

jgerrish_cycle_detection: jgerrish_cycle_detection.cpp graph.cpp
	$(CXX) -g -o $@ $^

tests: test

test: tests/test.cpp graph.cpp
	$(CXX) -I. -g -o $@ $^

clean:
	rm -f *.o
	rm -f jgerrish_cycle_detection
