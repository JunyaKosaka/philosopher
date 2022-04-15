#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		// child
		while (1)
		{
			printf("child process running\n");
			sleep(1);
		}
	}
	else
	{
		sleep(2);
		kill(pid, SIGINT);
		wait(NULL);
		printf("parent process done\n");
	}
	return (0);
}
