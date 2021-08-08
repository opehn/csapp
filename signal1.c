/* 주의 : 이 코드에는 버그가 있음*/
#include "csapp.h"

void handler1(int sig)
{
	int olderrno = errno;
	
	if ((waitpid(-1, NULL, 0)) < 0)
		sio_error("waitpid error");
	Sio_puts("Handler reaped chaild\n");
	Sleep(1);
	errno = olderrno;
}

int main()
{
	int i, n;
	char buf[MAXBUF];
	
	if (signal(SIGCHLD, handler1) == SIG_ERR)
		unix_error("signal error");

	/*부모가 자식 생성*/
	for (i = 0; i < 3; i++)	{
		if(Fork() == 0){
			printf("Hello from child %d\n", (int)getpid());
			exit(0);
		}	
	}

	/* 부모는 기다리다가 터미널 입력을 받으면 실행 */
	if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
		unix_error("read");

	printf("Parent processing input\n");
	while(1)
		;

	exit(0);
}
