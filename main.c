#include "philo.h"

/* ./philo no_philo t2die t2eat t2sleep [no_max_meals_each] */

int	main(int argc, char **argv)
{
	t_table table;

	check_input(argc, argv);
	initialize_data(argc, argv, &table);
	printf("number of philos: %d\n", table.philo_count);
	printf("time to die: %ld\n", table.time_to_die);
	printf("time to eat: %d\n", table.time_to_eat);
	printf("time to sleep: %d\n", table.time_to_sleep);
	printf("max meals each: %d\n", table.max_meals);
	start_threads(&table);
	free_both_arrays(&table);
	return (0);
}