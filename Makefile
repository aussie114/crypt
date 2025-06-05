OBJECTS = $(patsubst src/%.c, build/%.o, $(wildcard src/*.c))

build: $(OBJECTS)
	gcc build/*.o -o bin/crypt

run: build
	foot --app-id crypt -W 50x30 ./bin/crypt ./data/example.csv 2>/dev/null

build/%.o: src/%.c
	gcc -Wall -Wextra -Iinclude -c $< -o $@

clean:
	rm -rf build/* bin/*
