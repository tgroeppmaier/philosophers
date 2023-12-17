#include "philo.h"

int	ft_atoi(const char *str)
{
	int	c;
	int	sign;

	c = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		c = c * 10 + (*str - '0');
		str++;
	}
	return (c * sign);
}
