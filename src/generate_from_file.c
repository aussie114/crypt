#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <readline/readline.h>
#include "password_generator.h"

void generate_from_file(char * file_address)
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
	// Open file
	FILE * stream;
	char * line = NULL;
	size_t size = 0;
	stream = fopen(file_address, "r");
	if (stream == NULL) 
	{
		printf("Error opening file: %s", file_address);
	}
	// Iterate over file	
	int count = 0;
	while (getline(&line, &size, stream) != -1) 
	{
		// Strip newline
		line[strcspn(line, "\n")] = 0;
		char * original_line = strdup(line);
		// Split line by comma
		char * service  = strtok(line, ",");
		char * username = strtok(NULL, ",");
		char * length   = strtok(NULL, ",");
		char * special  = strtok(NULL, ",");

		if (!service || !username || !length || !special)
		{
			printf(
				"\nError: Line %d %s is malformed\n"
				"skipping...\n", count, original_line);
			free(original_line);
			continue;
		}
		// Generate and print password
		char password[257];
		generate_password(password, service, username, length, special, keyword);
		printf("\n/--------------------------------%s\n%s\n%s\n", service, username, password);
		free(original_line);
		count++;
	}
	puts("");
	free(line);
	fclose(stream);
}

