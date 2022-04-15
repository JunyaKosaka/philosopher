#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*str;

	str = (char *)malloc(1);
	free(str);
	return (0);
}
