PROJECT = crypt
OBJECTS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

run: build
	bin/$(PROJECT) data/example.csv

build: $(OBJECTS)
	gcc build/*.o -o bin/$(PROJECT) -lreadline

build/%.o: src/%.c
	gcc -Wall -Wextra -Iinclude -c $< -o $@

clean:
	rm -rf build/* bin/$(PROJECT)

