run: build
	./bin/crypt

build: build/generate_from_file.o build/generate_password.o build/generate_single.o build/global.o build/gtk_helper_functions.o build/main.o 
	gcc `pkg-config --libs gtk4` build/*.o -o ./bin/crypt

build/generate_from_file.o: include/generate_from_file.h src/generate_from_file.c
	gcc -c -Iinclude `pkg-config --cflags gtk4` src/generate_from_file.c -o build/generate_from_file.o

build/generate_password.o: include/generate_password.h src/generate_password.c
	gcc -c -Iinclude `pkg-config --cflags gtk4` src/generate_password.c -o build/generate_password.o

build/generate_single.o: include/generate_single.h src/generate_single.c
	gcc -c -Iinclude `pkg-config --cflags gtk4` src/generate_single.c -o build/generate_single.o

build/global.o: include/global.h src/global.c
	gcc -c -Iinclude `pkg-config --cflags gtk4` src/global.c -o build/global.o

build/gtk_helper_functions.o: include/gtk_helper_functions.h src/gtk_helper_functions.c
	gcc -c -Iinclude `pkg-config --cflags gtk4` src/gtk_helper_functions.c -o build/gtk_helper_functions.o

build/main.o: src/main.c
	gcc -c -Iinclude `pkg-config --cflags gtk4` src/main.c -o build/main.o

clean:
	rm build/*o ./bin/crypt
