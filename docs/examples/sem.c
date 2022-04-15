#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	sem_t	*sem;

	sem = sem_open("/unko", O_CREAT, 0600, 1); // unknown object

	printf("Lock\n");
	sem_wait(sem);
	printf("sleep 2 seconds\n");
	sleep(2);
	printf("Unlock\n");
	sem_post(sem);

	return (0);
}
