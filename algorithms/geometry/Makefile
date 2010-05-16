all: 
	doxygen Doxyfile
	make -C doc/latex pdf	
graph: src/graph.cpp
	g++ src/graph.cpp -o bin/graph
commit: doc
	rm -f bin/* doc/refman.pdf
	mv doc/latex/refman.pdf doc/
	rm -r doc/latex doc/html
build: src/graph.cpp
	g++ src/graph.cpp -o bin/graph
