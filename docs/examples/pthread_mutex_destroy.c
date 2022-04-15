// CELEBP36
#define _OPEN_THREADS
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int	main() {
	pthread_mutex_t mutex;

	if (pthread_mutex_init(&mutex, NULL) != 0) {
		perror("pthread_mutex_init() error");
		exit(1);
	}

	if (pthread_mutex_destroy(&mutex) != 0) {
		perror("pthread_mutex_destroy() error");
		exit(2);
	}
}
