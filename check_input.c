#include "philo.h"

static bool	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (true);
	else
		return (false);
}

static bool	is_in_range(long long num)
{
	if (num >= INT_MIN && num <= INT_MAX)
		return (true);
	else
		return (false);
}

static bool	is_valid_int(char *str)
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

bool	check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (5 != argc && 6 != argc)
		return (error_exit(false, "wrong argc\n"));
	while (++i < argc)
	{
		if (!(is_valid_int(argv[i])))
			return (error_exit(false, "not a valid integer\n"));
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (error_exit(false, "invalid philo number\n"));
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
		return (error_exit(false, "no time values lower than 60 allowed\n"));
	return (true);
}
