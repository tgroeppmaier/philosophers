#include "philo.h"

void	initialize_table(int argc, char **argv, t_table *table)
{
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		table->max_meals_each = -1;
	else
		table->max_meals_each = ft_atoi(argv[5]);
}

void	initialize_data(int argc, char **argv, t_table *table)
{
	initialize_table(argc, argv, table);
}