#include "philo.h"

/* ./philo no_philo t2die t2eat t2sleep [no_max_meals_each] */

bool	initialize_table(int argc, char **argv, t_table *table)
{
	int	err;

	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]) * 1e3;
	table->time_to_sleep = ft_atoi(argv[4]) * 1e3;
	if (argc == 5)
		table->max_meals = -1;
	else
		table->max_meals = ft_atoi(argv[5]);
	table->end_sim = false;
	table->even_philos = false;
	if (table->philo_count % 2 == 0)
		table->even_philos = true;
	err = pthread_mutex_init(&table->print_mutex, NULL);
	if (err != 0)
		return (error_exit(false, "Failed to initialize print_mutex\n"));
	err = pthread_mutex_init(&table->end_lock, NULL);
	if (err != 0)
		return (error_exit(false, "Failed to initialize end_mutex\n"));
	return (true);
}

int	main(int argc, char **argv)
{
	t_table table;

	if (!check_input(argc, argv))
		return (1);
	if (!initialize_table(argc, argv, &table))
		return (1);
	if (!initialize_data(&table))
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