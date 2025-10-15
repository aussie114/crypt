#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include "password_generator.h"

void generate_single(char * service, char * username, char * length, char * special)
{
	// Get the keyword
	char * keyword;
	keyword = readline("\nEnter keyword: ");
	printf(
		"\033[A"  // move
		"\033[2K" // clear"
		"Enter keyword: "
	);
	for (unsigned long i = 0; i < strlen(keyword); i++)
	{
		putchar('*');
	}
	putchar('\n');
	// Generate and print password
	char password[257];
	generate_password(password, service, username, length, special, keyword);
	printf("\n/--------------------------------%s\n%s\n%s\n", service, username, password);
	puts("");
}

