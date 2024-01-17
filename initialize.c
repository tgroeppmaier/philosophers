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
			free_philos(&array, i, false);
			destroy_table_mtx(table);
			return (NULL);
		}
		i++;
	}
	return (array);
}

t_fork	**create_fork_arr(t_table *table)
{
	t_fork	**array;
	int		i;

	i = 0;
	array = (t_fork **)malloc(sizeof(t_fork *) * table->philo_count);
	if (!array)
		return (NULL);
	while (i < table->philo_count)
	{
		array[i] = (t_fork *)malloc(sizeof(t_fork));
		if (!array[i])
		{
			free_forks(&array, i, false);
			free_philos(&table->philo_array, table->philo_count, false);
			destroy_table_mtx(table);
			return (NULL);
		}
		i++;
	}
	return (array);
}

bool	initialize_forks(t_table *table)
{
	int	i;
	int	err;

	i = 0;
	while (i < table->philo_count)
	{
		err = pthread_mutex_init(&table->fork_array[i]->fork, NULL);
		if (err != 0)
		{
			free_forks(&table->fork_array, i, false);
			free_philos(&table->philo_array, table->philo_count, false);
			destroy_table_mtx(table);
			return (false);
		}
		table->fork_array[i]->fork_id = i + 1;
		i++;
	}
	return (true);
}

/* the left fork is his own (id) and the right fork is the id of the philo
next in the array */

bool	initialize_philo(t_table *table)
{
	int	i;
	int	right_fork;

	i = -1;
	while (++i < table->philo_count)
	{
		right_fork = (i + 1) % table->philo_count;
		table->philo_array[i]->id = i + 1;
		table->philo_array[i]->full = false;
		table->philo_array[i]->table = table;
		table->philo_array[i]->left_fork = table->fork_array[i];
		table->philo_array[i]->right_fork = table->fork_array[right_fork];
		table->philo_array[i]->meals_counter = 0;
		table->philo_array[i]->last_meal_time = 0;
		table->philo_array[i]->alive = true;
		if (pthread_mutex_init(&table->philo_array[i]->lock, NULL) != 0)
		{
			free_forks(&table->fork_array, i, false);
			free_philos(&table->philo_array, table->philo_count, false);
			destroy_table_mtx(table);
			return (error_exit(false, "Failed to initialize philo lock\n"));
		}
	}
	return (true);
}

bool	initialize_data(t_table *table)
{
	table->philo_array = create_philo_arr(table);
	if (!table->philo_array)
		return (error_exit(false, "malloc fail creation philo array\n"));
	table->fork_array = create_fork_arr(table);
	if (!table->fork_array)
		return (error_exit(false, "malloc fail creation fork array\n"));
	if (!initialize_forks(table))
		return (false);
	if (!initialize_philo(table))
		return (false);
	return (true);
}
