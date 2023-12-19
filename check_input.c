#include "philo.h"

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

void	check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (5 != argc && 6 != argc)
		error_exit(1, "wrong argc\n");
	while (++i < argc)
	{
		if (!(is_valid_int(argv[i])))
			error_exit(1, "not valid integer\n");
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		error_exit(1, "invalid philo number\n");
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		error_exit(1, "no time values lower than 60 allowed\n");
}
