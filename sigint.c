#include "csapp.h"
#include <stdio.h>

void sigint_handler(int sig) /* SIGINT 핸들러*/
{
	printf("Caught SIGINT!\n");
	exit(0);
}

int main()
{
	/*SIGINT 핸들러 설치*/
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		printf("signal error");

	pause(); /*시그널 receipt 기다림*/

	return 0;
}
