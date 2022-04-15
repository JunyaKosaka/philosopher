#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define LOOP_NUM 50000
#define NR_THREADS 2
#define SEM_NAME "/semaphore"

void *func(void *arg)
{
	size_t i;
#ifndef NO_LOCK
	sem_t *sem = *(sem_t **)((void **) arg)[0];
#endif
	int *count = (int *)((void **) arg)[1];

	for (i = 0; i < LOOP_NUM; i++) {
#ifndef NO_LOCK

		if (sem_wait(sem) != 0) {
			fprintf(stderr, "Error: cannot lock\n");
			exit(1);
		}

		/* critical section with lock. */
		(*count)++;

		if (sem_post(sem) != 0) {
			fprintf(stderr, "Error: cannot unlock\n");
			exit(2);
		}

#else
		/* critical section without lock (interleaving increment operations). */
		(*count)++;
#endif
	}

	return NULL;
}

int main(void)
{
	pthread_t threads[NR_THREADS];
	size_t i;
	sem_t *sem;
	int count = 0;
	void *arg[] = {&sem, &count};

	if ((sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED) {
		perror("sem_open");
		exit(1);
	}

	for (i = 0; i < NR_THREADS; i++) {
		if (pthread_create(&threads[i], NULL, func, arg) != 0) {
			fprintf(stderr, "Error: cannot create thread %zu\n", i + 1);
			exit(2);
		}
	}

	for (i = 0; i < NR_THREADS; i++) {
		printf("execute pthread_join thread %zu\n", i + 1);

		if (pthread_join(threads[i], NULL) != 0) {
			fprintf(stderr, "Error: cannot join thread %zu\n", i + 1);
			exit(3);
		}
	}

	printf("count = %d\n", count);

	if (sem_close(sem) == -1) {
		perror("sem_close");
		exit(4);
	}

	if (sem_unlink(SEM_NAME) == -1) {
		perror("sem_unlink");
		exit(5);
	}

	return 0;
}
