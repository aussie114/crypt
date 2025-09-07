#!/bin/sh

if [ "$1" = "rebuild" ]; then
	cd src/ || exit 1
    for f in *.c; do
        echo "compiling $f..."
        "./$f" || exit 1
    done
	cd ..
fi

echo "compiling main.c..."
tail -n +20 "$0" | gcc -c -xc -Wall -Wextra -std=c99 - -o src/build/"$(basename "$0" .c).o"
echo "building crypt..."
gcc src/build/* -Wall -Wextra -std=c99 `pkg-config --libs gtk4` -o crypt
echo "running crypt ..."
./crypt data/example.csv
exit

int create_gtk(int argc, char ** argv);

int main (int argc, char ** argv)
{
	return create_gtk(argc, argv);
}
