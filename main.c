#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "my_parse.h"

#define CR 0x0D
#define LF 0x0A

int main(int argc, char *argv[])
{
	char ch;
	char buff[MAX_LINE_COUNT];
	int i, p;

	if (argc < 2)
		printf("INVALID ARGUMENT NUMBER!\n");

	FILE* f;
	f = fopen(argv[1], "rb");
	if (f == NULL)
	{
		perror("FAILED TO OPEN THE FILE!\n");
		return -1;
	}

	while (!feof(f))
	{
		ch = fgetc(f);
		if (ch == CR)
			printf("<CR>\n");
		else
			if (ch == LF)
				printf("<LF>\n");
			else
				printf("%c\n", ch);

		p = parse(ch);
		printf("Parse returned %d\n", p);
		if (p != 0)
			break;
	}
	return 0;
}