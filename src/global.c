#!/bin/sh
tail -n +5 "$0" | gcc -c -xc -Wall -Wextra -std=c99 `pkg-config --cflags gtk4` - -o build/"$(basename "$0" .c).o"
exit                                                                                                                                        

#include "global.h"
Widgets widgets = {0};
char * file_address = NULL;
