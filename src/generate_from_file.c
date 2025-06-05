#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "generate_password.h"

void generate_from_file(char * file_path)
{
	FILE * accounts_file = fopen(file_path, "r");

	if (!accounts_file)
	{
		fprintf(stderr, "File not found\n");
		return;
	}
	
	int line = 1;
	char line_buffer[256];
	char password[257];
	char * keyword = getpass("Enter keyword: ");
	while( fgets(line_buffer, 256, accounts_file ) != NULL  )
	{
		if (line_buffer[0] == '\n')
		{
			continue;
		}

		line_buffer[strcspn(line_buffer, "\n")] = '\0';

		char * service  = strtok(line_buffer, ",");
		char * username = strtok(NULL, ",");
		char * length   = strtok(NULL, ",");
		char * special  = strtok(NULL, ",");

		if (!service || !username || !length || !special) 
		{
			fprintf(stderr, "%d | \"%s\"\nMalformed line, skipping.\n\n", line, line_buffer);
			continue;
		}

		generate_password(password, service, username, length, special, keyword);
		printf("/--------------------------------%s\n%s\n%s\n\n", service, username, password);
		line++;
	}
	fclose(accounts_file);
}
