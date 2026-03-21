#include <stdio.h>
#include <string.h>

// ./a.out ipdatabase.csv 0.0.0.0/0 "IPV4 ROOT POOL - default route"

int main(int argc, char **argv)
{
//	char * ip = {"0.0.0.0/0"};
//	char * desc = {"IPV4 ROOT POOL - default route"};


	FILE * file = fopen(argv[1], "a");
	if (file == NULL && argc != 3)
		return 1;
	fprintf(file, "%s,%s\n", argv[2], argv[3]);
	fclose(file);

}
