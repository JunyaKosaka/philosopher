#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	microsecond;

	microsecond = 1.5 * 1000000; // 1.5秒止まる
	printf("start\n");
	usleep(microsecond);
	printf("end\n");
	return (0);
}
