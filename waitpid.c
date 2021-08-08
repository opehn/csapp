#include "csapp.h"
#define N 2

int main()
{
	int status, i;
	pid_t pid;

	/* 부모가 N 개의 자식 프로세스를 만든다 */
	for (i = 0; i < N; i++)
	{
		if ((pid = fork() == 0)) /* 자식 */
			exit(100+i);
	}
	/* 부모가 N개의 자식을 순서 없이 청소한다*/
	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if(WIFEXITED(status)) /* 정상적으로 종료시*/
			printf("child %d terminate normally with exit status=%d\n",
					pid, WEXITSTATUS(status));
		else
			printf("child %d terminated abnormally\n", pid);
	}

	/*더 이상 자식이 없어야 정상 종료 된다?*/
	if (errno != ECHILD)
		printf("waitpid error");
	//	unix_error("waitpid error");
	
	exit(0);
}
