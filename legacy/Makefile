OBJECTS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

run: build
	bin/crypt data/example.csv

build: $(OBJECTS)
	gcc `pkg-config --libs gtk4` build/*.o -o bin/crypt

build/%.o: src/%.c
	gcc -Wall -Wextra -Iinclude `pkg-config --cflags gtk4` -c $< -o $@

clean:
	rm -rf build/* bin/crypt

