doc: src/graph.cpp
	doxygen Doxyfile
	make -C doc/latex pdf	
graph: src/graph.cpp
	g++ src/graph.cpp -o bin/graph
clear:
	rm bin/*
commit: doc
	rm bin/*
	mv doc/latex/refman.pdf .
	rm -r doc/latex
	rm -r doc/html
