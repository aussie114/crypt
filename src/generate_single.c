#include <stdio.h>
#include <unistd.h>
#include <generate_password.h>

void generate_single(char * argv[])
{
	char * keyword = getpass("Enter keyword: ");

	char password[257];
	generate_password(password, argv[1], argv[2], argv[3], argv[4],  keyword);

	printf("/--------------------------------%s\n%s\n%s\n\n", argv[1], argv[2], password);
}
