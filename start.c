#include "philo.h"

/* depending on the boolean even, the function pointer is either set to philo_eat_even or 
philo_eat_odd. The loop continues until max meals is reached or indefinately in case of max_meals = -1
which indicates no limit */

void	philo_routine(t_philo *philo, bool even)
{
	bool	(*philo_eat)(t_philo *);

	if (even)
		philo_eat = philo_eat_even;
	else
		philo_eat = philo_eat_odd;
	while (philo->meals_counter < philo->table->max_meals
		|| philo->table->max_meals == -1)
	{
		if (philo_eat(philo) == false)
			break ;
		philo->meals_counter++;
		print_atomic(philo, "is sleeping\n");
		if (!custom_usleep(philo->table, philo->table->time_to_sleep))
			break ;
		if (!philo_think(philo))
			break ;
	}
	set_bool(&philo->lock, &philo->full, true);
}

void	*philo_start(void *data)
{
	t_philo	*philo;
	bool	even;

	philo = (t_philo *)data;
	if (philo->table->philo_count == 1)
	{
		print_status(philo, "has taken a fork\n");
		custom_usleep(philo->table, philo->table->time_to_die);
	}
	else
	{
		even = false;
		if (philo->id % 2 == 0)
			even = true;
		if (philo->id % 2 != 0)
			usleep(philo->table->time_to_eat / 2);
		philo_routine(philo, even);
	}
	return (NULL);
}

bool	start_threads(t_table *table)
{
	int	i;

	i = -1;
	gettimeofday(&table->start_time, NULL);
	print_status(table->philo_array[0], "start time\n");
	while (++i < table->philo_count)
	{
		if (pthread_create(&table->philo_array[i]->thread_id, NULL, philo_start,
				table->philo_array[i]) != 0)
		{
			free_table(table, true);
			return (error_exit(false, "thread creation failed\n"));
		}
	}
	pthread_create(&table->sup_thread_id, NULL, supervisor, table);
	i = -1;
	while (++i < table->philo_count)
		pthread_join(table->philo_array[i]->thread_id, NULL);
	pthread_join(table->sup_thread_id, NULL);
	print_status(table->philo_array[0], "end of simulation\n");
	return (true);
}
