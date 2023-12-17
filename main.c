#include "philo.h"

bool	check_input(int argc, char **argv)
{
	int	i;

	i = 0;
	if (5 != argc && 6 != argc)
	{
		printf("wrong input count\n");
		return (false);
	}
	while (++i < argc)
	{
		if (!(is_valid_int(argv[i])))
		{
			printf("not a valid int\n");
			return (false);
		}
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table table;

	if (!check_input(argc, argv))
		return (1);
	return (0);
}