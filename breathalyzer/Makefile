all: breathalyzer

breathalyzer: breathalyzer.cpp trie.cpp
	$(CXX) -O2 -o $@ $^
	#$(CXX) -g -o $@ $^

clean:
	rm -f *.o
	rm -f breathalyzer
