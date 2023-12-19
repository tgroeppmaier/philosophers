#include "philo.h"

t_philo	**create_philo_arr(t_table *table)
{
	t_philo	**array;
	int		i;

	i = 0;
	array = (t_philo **)malloc(sizeof(t_philo *) * table->philo_count);
	if (!array)
		return (NULL);
	while (i < table->philo_count)
	{
		array[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!array[i])
		{
			free_array((void ***)&array, i);
			return (NULL);
		}
		// printf("i = %d\n", i);
		i++;
	}
	return (array);
}

t_fork **create_fork_arr(t_table *table)
{
	t_fork **array;
	int	i;

	i = 0;
	array = (t_fork **)malloc(sizeof(t_fork *) * table->philo_count);
	if(!array)
		return(NULL);
	while (i < table->philo_count)
	{
		array[i] = (t_fork *)malloc(sizeof(t_fork));
		if (!array[i])
		{
			free_array((void ***)table->philo_array, i);
			free_array((void ***)&array, i);
			return (NULL);
		}
		i++;
	}
	return(array);
}

void	initialize_table(int argc, char **argv, t_table *table)
{
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]) * 1e3;
	table->time_to_eat = ft_atoi(argv[3]) * 1e3;
	table->time_to_sleep = ft_atoi(argv[4]) * 1e3;
	if (argc == 5)
		table->max_meals_each = -1;
	else
		table->max_meals_each = ft_atoi(argv[5]);
	table->end_simulation = false;
}

void	initialize_data(int argc, char **argv, t_table *table)
{
	initialize_table(argc, argv, table);
	table->philo_array = create_philo_arr(table);
	if (!table->philo_array)
		error_exit(1, "malloc fail creation philo array\n");
	table->fork_array = create_fork_arr(table);
	if (!table->philo_array)
		error_exit(1, "malloc fail creation fork array\n");
}