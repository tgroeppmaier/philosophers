#include <stdbool.h>
#include <unistd.h>
#include <limits.h>

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

bool	is_in_range(long long num)
{
	if (num >= INT_MIN && num <= INT_MAX)
		return (true);
	else
		return (false);
}

bool	is_valid_int(char *str)
{
	int			i;
	int			sign;
	long long	c;

	if (NULL == str)
		return (false);
	i = 0;
	c = 0;
	sign = 1;
	if (str[0] == '-')
		sign = -1;
	if (str[0] == '+' || str[0] == '-')
		i++;
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		c = c * 10 + (str[i] - '0');
		if (!is_in_range(c * sign))
			return (false);
		i++;
	}
	return (true);
}
