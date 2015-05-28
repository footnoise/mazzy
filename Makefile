prog: src/mazzy.o
	g++ -o mazzy src/mazzy.o
clean:
	rm -f mazzy
	rm -f src/*.o
	rm -f *~