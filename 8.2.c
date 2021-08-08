#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int a = 9;

	if (fork() == 0)
		printf("p1: a = %d\n", a--);
	else
		printf("p2: a = %d\n", a++);
	exit(0);
}
