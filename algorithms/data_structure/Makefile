all:
	rm doc/refman.pdf -f
	doxygen Doxyfile
	make -C doc/latex pdf
	mv doc/latex/refman.pdf doc/
	rm doc/latex doc/html -r -f

