Hcc: Hcc.c

test: Hcc
	./test.sh

clean:
	rm -f Hcc *.o *~ tmp*