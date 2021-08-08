#include "csapp.h"

/*주의 : 이 코드는 버그가 있음*/
void handler(int sig)
{
	int olderrno = errno;
	sigset_t mask_all, prev_all;
	pid_t pid;

	Sigfillset(&mask_all);
	while((pid = waitpid(-1, NULL, 0)) > 0) { /*좀비 청소*/
		Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
		deletejob(pid); /*job 리스트에서 자식 삭제*/
		Sigprocmask(SIG_SETMASK, &prev_all, NULL);
	}
	
	if (errno != ECHILD)
		Sio_error("waitpid error");
	errno = olderrno;
}

int main(int argc, char **argv)
{
	int pid;
	sigset_t mask_all, prev_all;

	Sigfillset(&mask_all);
	Signal(SIGCHLD, handler);
	initjobs(); /*job 리스트 초기화*/

	while (1) {
		if ((pid = Fork()) == 0) { /*자식 프로세스일 경우*/
			Execve("/bin/date", argv, NULL);
		}
		Sigprocmask(SIG_BLOCK, &mask_all, &prev_all); /*부모 프로세스일 경우*/
		addjob(pid); /*자식을 job 리스트에 넣는다*/
		Sigprocmask(SIG_SETMASK, &prev_all, NULL); 
	}
}
