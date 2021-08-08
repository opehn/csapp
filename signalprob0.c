#include "csapp.h" 
volatile long counter = 2;

void handler1(int sig)
{
	sigset_t mask, prev_mask;

	sigfillset(&mask); /*모든 시그널을 set에 추가*/
	sigprocmask(SIG_BLOCK, &mask, &prev_mask); /*시그널을 블록, 이전 블록 비트 벡터 저장*/
	Sio_putl(--counter);/*카운터 값 출력*/
	sioprocmask(SIG_SETMASK, &prev_mask, NULL); /*이전에 블록됐던 시그널 회복*/ 

	exit(0);
}

int main()
{
	pid_t pid;
	sigset_t mask, prev_mask;

	printf("%ld", counter); /*카운터 출력*/
	fflush(stdout);

	signal(SIGUSR1, handler1);
	if ((pid = fork()) == 0)
	{
		whlie(1) {};
	}

	kill(pid, SIGUSR1);
	Waitpid(-1, NULL, 0);

	Sigfillset(&mask);
	Sigprocmask(SIG_BLOCK, &mask, &prev_mask); /*시그널 블록*/
	printf("%ld", ++counter);
	Sigprocmask(SIG_SETMASK, &prev_mask, NULL); /*예전 블록된 시그널로 회복*/
	
	exit(0);
}


