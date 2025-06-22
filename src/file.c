#include <stdio.h>

char * file_address = NULL;
int line_buffer_size = 0;

void get_line_buffer_size()
{
	FILE * file = fopen(file_address, "r");
	if (!file)
	{
		return;
	}
	int length  = 0;
	int longest = 0;
	char ch;
	while ( (ch = fgetc(file)) != EOF )
	{
		length++;
		if (ch == '\n')
		{
			if (length > longest)
			{
				longest = length;
			}
			length = 0;
		}
	}
	line_buffer_size = longest;
	fclose(file);
}

