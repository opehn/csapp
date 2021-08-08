#include "csapp.h"
#define N 2

int main()
{
	int status, i;
	pid_t pid[N], retpid;

	/* N 개의 자식 프로세스 만들기*/
	for (i = 0; i < N; i++)
		if(pid = fork() == 0) /* 자식이라면 */
			exit(100+i);

	/*부모가 N개의 자식을 순서대로 청소*/
	i = 0;
	while((retpid = waitpid(pid[i++], &status, 0)) > 0) {
		if(WIFEXITED(status))
			printf("child %d terminate normally with exit status=%d\n",
					retpid, WEXITSTATUS(status));
		else
			printf("child %d terminated abnormally\n", retpid);
	}

	/*자식이 없을 때 종료*/
	if (errno != ECHILD)
		unix_error("waitpid error");

	exit(0);
}
