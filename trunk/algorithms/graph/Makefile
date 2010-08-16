all:	documentation commit
	make documentation
	make commit
documentation: 
	doxygen Doxyfile
	make -C doc/latex pdf	
graph: src/graph.cpp
	${CXX} src/graph.cpp -o bin/graph
commit: documentation
	rm -f bin/* doc/refman.pdf
	mv doc/latex/refman.pdf doc/
	rm -r doc/latex doc/html
build: src/graph.cpp
	${CXX} src/graph.cpp -o bin/graph
