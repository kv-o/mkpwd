#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define CHARSET "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

/* not truly random */
char
randchar(void)
{
	size_t setlen = sizeof(CHARSET) - 1;
	int randnum = rand() % setlen;
	return CHARSET[randnum];
}

char*
mkpwd(size_t len)
{
	int i = 0;
	char *password = malloc(len + 1);
	if (password == NULL)
		return NULL;
	password[len] = '\0';
	for (i = 0; i < len; i++)
		password[i] = randchar();
	return password;
}

int
main(int argc, char *argv[])
{
	int i;
	int len = 10;
	int num = 1;
	int lflag = 0;
	int nflag = 0;
	char *password;
	srand(time(NULL));

	/* have not practised using getopt */
	if (argc == 3 && !strcmp(argv[1], "-l")) {
		lflag = 2;
	} else if (argc == 3 && !strcmp(argv[1], "-n")) {
		nflag = 2;
	} else if (argc == 5 && !strcmp(argv[1], "-l") && !strcmp(argv[3], "-n")) {
		lflag = 2;
		nflag = 4;
	} else if (argc == 5 && !strcmp(argv[1], "-n") && !strcmp(argv[3], "-l")) {
		nflag = 2;
		lflag = 4;
	} else if (argc != 1) {
		fprintf(stderr, "mkpwd: invalid invocation\n");
		return 1;
	}

	if (lflag != 0)
		len = atoi(argv[lflag]);
	if (nflag != 0)
		num = atoi(argv[nflag]);
	if (len == 0 || num == 0) {
		fprintf(stderr, "mkpwd: invalid invocation\n");
		return 1;
	}

	for (i = 0; i < num; i++) {
		password = mkpwd(len);
		if (password == NULL) {
			fprintf(stderr, "mkpwd: out of memory\n");
			return 1;
		}
		printf("%s\n", password);
		free(password);
	}
}
