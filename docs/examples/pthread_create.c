#include "stdio.h"
#include "pthread.h"

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

	pthread_t pthread;
	pthread_create(&pthread, NULL, &func_thread, &b);

	int i=0;
	for(i=0; i < 10000; i++){
		pthread_mutex_lock(&mutex);
		int next = g_num + 1;
		int now = g_num;
		g_num = next;
		pthread_mutex_unlock(&mutex);
		if (now+1 != next) {
			printf("other theard change %d %d\n", now, next);
		}
	}
	pthread_join(pthread, NULL); // pthreadで作られたスレッドが終わるまで待つ
	printf("g_num=%d\n", g_num);
	// pthread_mutex_destroy(&mutex);
	return 0;
}
