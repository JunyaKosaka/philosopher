#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

// struct timeval
// {
// 	time_t		tv_sec; // Seconds long型
// 	suseconds_t	tv_usec; // Microseconds  int型
// }

int	main(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	printf("%ld %06d\n", tv.tv_sec, tv.tv_usec);
	gettimeofday(&tv, NULL);
	printf("%ld %06d\n", tv.tv_sec, tv.tv_usec);
	return (0);
}
