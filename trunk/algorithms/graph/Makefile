doc: src/graph.cpp
	doxygen Doxyfile
	make -C doc/latex pdf	
graph: src/graph.cpp
	g++ src/graph.cpp -o bin/graph
clear:
	rm bin/*
