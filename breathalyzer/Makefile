all: breathalyzer

breathalyzer: breathalyzer.cpp trie.cpp
	$(CXX) -g -o $@ $^

clean:
	rm -f *.o
	rm -f breathalyzer
