#include <stdio.h>
#include <unistd.h>
#include "generate_from_file.h"
#include "generate_single.h"

int main(int argc, char * argv[])
{
	if      (argc == 2)
	{
		generate_from_file(argv[1]);
	}
	else if (argc == 5)
	{
		generate_single(argv);		
	}
	else
	{
		puts("Usage:\n\tcrypt.py service username length special\n\tcrypt.py /address/to/csv/file");
	}
	printf("Press return to quit...");
	getchar();
}
