#include "cdai_test.h"

char *strjoin(char *str1, char *str2)
{
	char *res = malloc(strlen(str1) + strlen(str2) + 1);
	for (unsigned long i = 0; i < strlen(str1); i++)
		res[i] = str1[i];
	for (unsigned long i = 0; i < strlen(str2); i++)
		res[strlen(str1) + i] = str2[i];
	res[strlen(str1) + strlen(str2)] = 0;

	return res;
}
