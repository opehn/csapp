#include "csapp.h"
#define MAXARGS	128
/*parseline - 명령줄 입력을 분석하고 argv 배열을 만듬*/
int parseline(char *buf, char **argv)
{
	char *delim;	/*첫 번째 스페이스 구분자를 가리키는 포인터 */
	int argc;		/* 인자의 갯수 */
	int bg; 		/*Background job?*/

	buf[strlen(buf)-1] = ' '; /*따라붙는 '\n'을 스페이스로 교체*/
	while (*buf && (*buf == ' ')) /* 첫 스페이스를 무시*/
		buf++;

	/* argv 배열 만들기 */
	argc = 0;
	while ((delim = strchr(buf, ' '))) {
		argv[argc++] = buf;
		*delim = '\0';
		buf = delim + 1;
		while (*buf && (*buf == ' ')) /* 스페이스 무시 */
			buf++;
	}
	argv[argc] = NULL;

	if (argc == 0) /* 빈 줄 무시 */
		return 1;
	
	/* 백그라운드에서도 실행되어야 하는가?*/
	if ((bg = (*argv[argc-1] == '&')) != 0)
		argv[--argc] = NULL;

	return bg;
}


/*eval - 명령줄 입력을 계산 */
void eval(char *cmdline)
{
	char *argv[MAXARGS]; /*execve() 함수의 인자 리스트*/
	char buf[MAXLINE];
	int bg;
	pid_t pid;

	strcpy(buf, cmdline);
	bg = parseline(buf, argv);
	if (argv[0] == NULL)
		return; /*빈 줄은 무시된다*/

	if(!builtin_command(argv)) {
		if((pid = fork()) == 0) {/* 자식 프로세스가 사용자 일 실행*/
			if (execve(argv[0], argv, environ) < 0) {
			printf("%s: Command not found.\n", argv[0]);
			exit(0);
			}	
		}
	/*선행 작업이 완료될 때까지 부모는 wait*/
	if (!bg) {
		int status;
		if (waitpid(pid, &status, 0) < 0)
			unix_error("waitfg: waitpid error");
		}
	else
		printf("%d %s", pid, cmdline);

	}
	return;
}


/*프로토타입*/
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

int main()
{
	char cmdline[MAXLINE]; /*커맨드 라인*/
	
	while (1){ /*무한 루프*/
		/* 읽기 단계 */
		printf("> ");
		fgets(cmdline, MAXLINE, stdin);
		if (feof(stdin))
			exit(0);

		/* 평가 단계*/
		eval(cmdline);
	}
}
