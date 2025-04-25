#include <gtk/gtk.h>

gchar * sha256_hash(const gchar * str) {
    GChecksum * checksum = g_checksum_new(G_CHECKSUM_SHA256);
    g_checksum_update(checksum, (const guchar*)str, -1);
    
    gchar * digest = g_strdup(g_checksum_get_string(checksum));
    g_checksum_free(checksum);
    
    return digest;
}

char * charactors = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*";
void generate_password(char output[], char * service, char * username, char * length, char * special, char * keyword)
{
	// ------------------------------------------------------------------------------------------ hash inputs
	char * hashes[] = 
	{
		sha256_hash(service),
		sha256_hash(username),
		sha256_hash(length),
		sha256_hash(special),
		sha256_hash(keyword)
	};
	// -------------------------------------------------------- Zips 256 hashes together into a single string
	char hash_string[321] = {'\0'};
	for (int i = 0, j = 0; i < 320; i += 5, j++)
	{
		for (int k = 0; k < 5; k++)
		{
			hash_string[i+k]   = hashes[k][j];
		}
	}
	// ------------------------------------------------------------------------------------------ Free hashes
	g_free(hashes[0]);
	g_free(hashes[1]);
	g_free(hashes[2]);
	g_free(hashes[3]);
	g_free(hashes[4]);
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
	long long password_length = g_ascii_strtoll(length, NULL, 10);
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
