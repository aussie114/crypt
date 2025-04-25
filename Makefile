run: build
	./bin/crypt

build: build/main.o
	gcc build/*.o -o ./bin/crypt

build/main.o: src/main.c
	gcc -c -Iinclude src/main.c -o build/main.o

clean:
	rm build/*o ./bin/crypt
