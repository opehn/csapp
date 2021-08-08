#include "csapp.h"

unsigned int wakeup (unsigned int secs);

void handler(int sig)
{
	return; /* 시그널을 잡아서 리턴*/
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{	
		printf("usage : type single number");
		exit(0);
	}	
	
	if(signal(SIGINT, handler)== SIG_ERR)
		printf("signal error");
	wakeup(atoi(argv[1]));
	exit(0);
} 
