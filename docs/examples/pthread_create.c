# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

int g_num = 0;
pthread_mutex_t mutex;

void *func_thread(void *p) {
	printf("start %d\n", *(int*)p);

	int i=0;
	for(i=0; i < 10000; i++){
		pthread_mutex_lock(&mutex);
		int next = g_num + 1;
		int now = g_num;
		g_num = next;
		usleep(100);
		pthread_mutex_unlock(&mutex);
		if (now+1 != next) {
			printf("other theard change %d %d\n", now, next);
		}
	}
	return 0;
}

int main(void) {
	pthread_mutex_init(&mutex, NULL);
	printf("test\n");

	int b = 42;

	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("%ld %06d\n", tv.tv_sec, tv.tv_usec);

	pthread_t pthread;
	pthread_create(&pthread, NULL, &func_thread, &b);

	int i=0;
	for(i=0; i < 10000; i++){
		pthread_mutex_lock(&mutex);
		int next = g_num + 1;
		int now = g_num;
		g_num = next;
		usleep(100);
		pthread_mutex_unlock(&mutex);
		if (now+1 != next) {
			printf("other theard change %d %d\n", now, next);
		}
	}
	pthread_join(pthread, NULL); // pthreadで作られたスレッドが終わるまで待つ
	printf("g_num=%d\n", g_num);
	// pthread_mutex_destroy(&mutex);
	gettimeofday(&tv, NULL);
	printf("%ld %06d\n", tv.tv_sec, tv.tv_usec);
	return 0;
}
