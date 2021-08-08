#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	if (fork() == 0)
	{
		printf("9"); fflush(stdout);
	}
	else
	{
		printf("0");
		fflush(stdout);
		waitpid(-1, NULL, 0);
	}
	printf("3");
	fflush(stdout);
	printf("6");
	exit(0);
}
