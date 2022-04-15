#include <stdio.h>
#include <pthread.h>

size_t const thread_no = 5;
char mess[] = "This is a test";

void *message_print(void *ptr){
	int error = 0;
	char *msg;

	/* スレッドをデタッチ */
	error = pthread_detach(pthread_self());
	/* もしあればエラー処理 */

	msg = (char *) ptr;
	printf("THREAD: This is the Message %s\n", msg);
	return (NULL);
}

int main(void) {
	int error = 0;
	size_t i = 0;
	/* スレッドプールを作成 */
	pthread_t thr[thread_no];

	for(i = 0; i < thread_no; i++) {
		error = pthread_create( &(thr[i]), NULL, message_print, (void *) mess);
		/* エラー処理 */
	}
	printf("MAIN: Thread Message: %s\n", mess);
	pthread_exit(NULL);
	return (0);
}
