#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_mut
{
	pthread_mutex_t	*mutex;
	int				*cnt;
	int				id;
}	t_mut;

const int U = 1000;

void	*func(void *p)
{
	t_mut	*t;
	int		i;
	
	t = p;
	i = -1;
	while (++i < U)
	{
		pthread_mutex_lock(t->mutex);
		++t->cnt;
		pthread_mutex_unlock(t->mutex);
		if (i % 10000 == 0) printf("id:%d\n", t->id);
		usleep(2000);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	thread3;
	pthread_t	thread4;
	int			cnt;

	pthread_mutex_t	mutex;

	struct timeval	tv;
	gettimeofday(&tv, NULL);
	printf("%ld %06d \n", tv.tv_sec, tv.tv_usec);
	pthread_mutex_init(&mutex, NULL);
	t_mut t;

	cnt = 0;
	t.mutex = &mutex;
	t.cnt = &cnt;
	t.id = 1;	

	pthread_create(&thread1, NULL, &func, &t);
	t_mut	t2;
	t2.mutex = &mutex;
	t2.cnt = &cnt;
	t2.id = 2;
	pthread_create(&thread1, NULL, &func, &t2);
	t_mut	t3;
	t3.mutex = &mutex;
	t3.cnt = &cnt;
	t3.id = 3;
	pthread_create(&thread1, NULL, &func, &t3);
	t_mut	t4;
	t4.mutex = &mutex;
	t4.cnt = &cnt;
	t4.id = 4;
	pthread_create(&thread1, NULL, &func, &t4);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	pthread_join(thread4, NULL);
	// printf("%d\n", cnt);
	struct timeval	tv2;
	gettimeofday(&tv2, NULL);
	printf("%ld %06d \n", tv2.tv_sec - tv.tv_sec, tv2.tv_usec - tv.tv_usec);

	return (0);
}
