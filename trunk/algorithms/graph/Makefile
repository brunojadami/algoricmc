all: graph
	doxygen Doxyfile
graph: src/graph.cpp
	g++ src/graph.cpp -o bin/graph
clear:
	rm bin/*
