#include "philo.h"

bool	check_philo_alive(t_table *table, int i, long current_time,
		int *full_philos)
{
	long	last_meal;
	long	time_diff;

	if (get_bool(&table->philo_array[i]->lock,
			&table->philo_array[i]->full) == true)
		(*full_philos)++;
	last_meal = get_long(&table->philo_array[i]->lock,
			&table->philo_array[i]->last_meal_time);
	time_diff = current_time - last_meal;
	if (time_diff > table->time_to_die)
	{
		pthread_mutex_lock(&table->philo_array[i]->lock);
		pthread_mutex_lock(&table->end_lock);
		print_status(table->philo_array[i], "\033[31mdied\033[0m");
		table->end_sim = true;
		table->philo_array[i]->alive = false;
		pthread_mutex_unlock(&table->end_lock);
		pthread_mutex_unlock(&table->philo_array[i]->lock);
		return (false);
	}
	return (true);
}

void	*supervisor(void *data)
{
	int		i;
	int		full_philos;
	long	current_time;
	t_table	*table;

	table = (t_table *)data;
	while (get_bool(&table->end_lock, &table->end_sim) != true)
	{
		i = -1;
		full_philos = 0;
		while (++i < table->philo_count)
		{
			current_time = get_time_diff(table->start_time);
			if (!check_philo_alive(table, i, current_time, &full_philos))
				return (NULL);
		}
		if (full_philos == table->philo_count)
		{
			pthread_mutex_lock(&table->end_lock);
			table->end_sim = true;
			pthread_mutex_unlock(&table->end_lock);
			break ;
		}
	}
	return (NULL);
}
