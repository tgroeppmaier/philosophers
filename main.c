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

/* ./philo no_philo t2die t2eat t2sleep [no_max_meals_each] */

int	main(int argc, char **argv)
{
	t_table table;

	if (!check_input(argc, argv))
		return (1);
	initialize_data(argc, argv, &table);
	printf("number of philos: %d\n", table.philo_count);
	printf("time to die: %d\n", table.time_to_die);
	printf("time to eat: %d\n", table.time_to_eat);
	printf("time to sleep: %d\n", table.time_to_sleep);
	printf("max meals each: %d\n", table.max_meals_each);
	return (0);
}