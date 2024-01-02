#include "philo.h"

/* ./philo no_philo t2die t2eat t2sleep [no_max_meals_each] */

int	main(int argc, char **argv)
{
	t_table table;

	if (!check_input(argc, argv))
		return (1);
	if (!initialize_data(argc, argv, &table))
		return (1);
	printf("number of philos: %d\n", table.philo_count);
	printf("time to die: %ld\n", table.time_to_die);
	printf("time to eat: %d\n", table.time_to_eat);
	printf("time to sleep: %d\n", table.time_to_sleep);
	printf("max meals each: %d\n", table.max_meals);
	if (!start_threads(&table))
		return (1);
	free_table(&table, true);
	return (0);
}