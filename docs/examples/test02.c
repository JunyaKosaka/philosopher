#include <pthread.h>
#include <stdio.h>

const int	U = 100000;

typedef struct s_mut
{
	pthread_mutex_t	*mutex;
	int				*cnt;
	int				id;
}	t_mut;

void *func(void *p)
{
	t_mut	*t;
	
	t = p;
	for (int i = 0; i < U; ++i)
	{
		pthread_mutex_lock(t->mutex);
		++(*t->cnt);
		pthread_mutex_unlock(t->mutex);
		if (i % 10000 == 0)
			printf("%d\n", t->id);
	}
	return (NULL);
}

int	main(void)
{
	int			cnt = 0;
	pthread_t	thread1;
	pthread_t	thread2;

	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);

	t_mut	t;
	t.mutex = &mutex;
	t.cnt = &cnt;

	t.id = 1;
	pthread_create(&thread1, NULL, &func, &t);

	t_mut	t2;
	t2.mutex = &mutex;
	t2.cnt = &cnt;
	t2.id = 2;
	pthread_create(&thread2, NULL, &func, &t2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("cnt: %d\n", *t.cnt);
}
