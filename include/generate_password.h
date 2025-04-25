#ifndef GENERATE_PASSWORD_H
#define GENERATE_PASSWORD_H
gchar * sha256_hash(const gchar * str);
void generate_password(char output[], char * service, char * username, char * length, char * special, char * keyword);
#endif
