#include <stdio.h>
#include <stdlib.h>
#include "sha256.h"

char * charactors = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
void generate_password(char output[], char * service, char * username, char * length, char * special, char * keyword)
{
	// ------------------------------------------------------------------------------------------ hash inputs
	char hashes[5][65];
	sha256(service,  hashes[0]);
	sha256(username, hashes[1]);
	sha256(length,   hashes[2]);
	sha256(special,  hashes[3]);
	sha256(keyword,  hashes[4]);
	// -------------------------------------------------------- Zips 256 hashes together into a single string
	char hash_string[321] = {'\0'};
	for (int i = 0, j = 0; i < 320; i += 5, j++)
	{
		for (int k = 0; k < 5; k++)
		{
			hash_string[i+k]   = hashes[k][j];
		}
	}
	// ------------------------------------------------------------------------------ Gets initial seed value
	unsigned long long seed_value = 0;
	unsigned long long seed_value_capped = 0;
	for (int i = 0; i < 320; i++)
	{
		seed_value += hash_string[i];
	}
	// ------------------------------------------------------------------------------------------- Sets range
	unsigned int flags[4] = {0}; // lower case, upper case, numerica. special
	int cap = 70;
	if (special[0] == 'f')
	{
		cap = 62;
		flags[3] = 1;
	}
	// --------------------------------------------------------------------------------- Generates a password
	int attempt = 0;
	long long password_length = strtol(length, NULL, 10);
	while (1)
	{
		for (int i = 0; i < 257; i++)
		{
			output[i] = '\0';
		}
		attempt += 1;
		for (int i = 0; i < password_length; i++)
		{
			seed_value += hash_string[i];
			seed_value_capped = seed_value % cap;
			flags[0] += (seed_value_capped <= 25);
			flags[1] += (seed_value_capped >= 26) && (seed_value_capped <= 51);
			flags[2] += (seed_value_capped >= 52) && (seed_value_capped <= 61);
			flags[3] += (seed_value_capped >= 62);
			output[i] = charactors[seed_value_capped];
		}
		// ----------------------------------------------------------------------- Returns after 100 attempts
		if (attempt >= 100)
		{
			return;
		}
		// ------------------------------------------------------------------------------------- Checks flags
		if ((flags[0] > 0) && (flags[1] > 0) && (flags[2] > 0) && (flags[3] > 0))
		{
			return;
		}
		// -------------------------------------------------------------------------------- Password rejected
		//g_print("Password rejected: %s flags: %d, %d, %d, %d\n", output, flags[0], flags[1], flags[2], flags[3]);
		flags[0] = 0;
		flags[1] = 0;
		flags[2] = 0;
		if (special[0] == 'f')
		{
			flags[3] = 1;
		}
		else
		{
			flags[3] = 0;
		}
	}
}
