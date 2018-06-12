#include <stdlib.h>	/* needed for exit() */
#include <unistd.h>	/* needed for isatty() */
#include <stdio.h>	/* needed for printf() */

int		main(int argc, char **argv)
{
	char	buf[1];

	if (isatty(0))
		printf("the standard input is from a terminal\n");
	else
	{
		printf("the standard input is NOT from a terminal\n");
		while (read(0, buf, 1) == 1)
			printf("%c", buf[0]);
	}
	if (isatty(1))
		printf("the standard output is to a terminal\n");
	else
		printf("the standard input is NOT to a terminal\n");
	exit(0);
}
