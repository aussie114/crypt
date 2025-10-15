#include <stdio.h>
#include "generate_from_file.h"
#include "generate_single.h"

int main (int argc, char ** argv)
{
	if (argc == 2)
	{
		generate_from_file(argv[1]);
	}
	else if (argc == 5)
	{
		generate_single(argv[1], argv[2], argv[3], argv[4]);
	}

	printf("Press enter to quit...");  
	getchar();

	return 0;

}
