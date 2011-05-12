all: breathalyzer

breathalyzer: breathalyzer.cpp trie.cpp
	$(CXX) -O2 -o $@ $^

clean:
	rm -f *.o
	rm -f breathalyzer
