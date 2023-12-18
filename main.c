#include "philo.h"

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
	if(ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		error_exit(1, "invalid philo number\n");
	if(ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60 )
		error_exit(1, "no time values lower than 60 allowed\n");
}

/* ./philo no_philo t2die t2eat t2sleep [no_max_meals_each] */

int	main(int argc, char **argv)
{
	t_table table;

	check_input(argc, argv);
	initialize_data(argc, argv, &table);
	printf("number of philos: %d\n", table.philo_count);
	printf("time to die: %d\n", table.time_to_die);
	printf("time to eat: %d\n", table.time_to_eat);
	printf("time to sleep: %d\n", table.time_to_sleep);
	printf("max meals each: %d\n", table.max_meals_each);
	return (0);
}