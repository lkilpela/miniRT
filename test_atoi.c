#include "libft.h"

int main ()
{
	char str[] = "-2147483648";
	printf("%d\n", ft_atoi(str));
	printf("%d\n", atoi(str));
	return (0);
}