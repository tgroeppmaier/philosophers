#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long	time_diff;

	time_diff = get_time_diff(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld ms: %ld %s\n", time_diff, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
void	print_status_nbr(t_philo *philo, char *status, long nbr)
{
	long	time_diff;

	time_diff = get_time_diff(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld ms: %ld %s %ld\n", time_diff, philo->id, status, nbr);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	philo_routine_even(t_philo *philo)
{
	// long time_diff;

	while (philo->meals_counter < philo->table->max_meals
		|| philo->table->max_meals == -1)
	{
		// time_diff = get_time_diff(philo->table->start_time) - philo->last_meal_time;
		// print_last_meal_time(philo);
		// printf("time diff = %ld\n", time_diff);
		if(get_long(&philo->table->end_lock, &philo->table->end_simulation) == 1)
			break;
		if(philo_eat_even(philo) == 1)
			break;
		philo->meals_counter++;
		print_status_nbr(philo, "meals eaten:", philo->meals_counter);
		if(philo->meals_counter == philo->table->max_meals)
			break;
		print_status(philo, "is sleeping\n");
		usleep(philo->table->time_to_sleep);
		print_status(philo, "is thinking\n");
		// usleep(philo->table->time_to_eat / 2);
		usleep(1000);
	}
	set_bool(&philo->lock, &philo->full, true);
}

void	philo_routine_odd(t_philo *philo)
{
	// long time_diff;

	if (philo->id != 1) 
		usleep(philo->table->time_to_eat);
	while (philo->meals_counter < philo->table->max_meals
		|| philo->table->max_meals == -1)
	{
		// time_diff = get_time_diff(philo->table->start_time) - philo->last_meal_time;
		// print_last_meal_time(philo);
		// printf("time diff = %ld\n", time_diff);
		if(get_long(&philo->table->end_lock, &philo->table->end_simulation) == 1)
			break;
		if(philo_eat_odd(philo) == 1)
			break;
		philo->meals_counter++;
		print_status_nbr(philo, "meals eaten:", philo->meals_counter);
		if(philo->meals_counter == philo->table->max_meals)
			break;
		print_status(philo, "is sleeping\n");
		usleep(philo->table->time_to_sleep);
		print_status(philo, "is thinking\n");
		// usleep(philo->table->time_to_eat / 2);
		usleep(1000);
	}
	set_bool(&philo->lock, &philo->full, true);
}

void	*philo_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	// wait_until_time(philo->table->start_time, 1e5);
	if (philo->id % 2 == 0)
	{
		philo_routine_even(philo);
	}
	else
	{
		philo_routine_odd(philo);
	}
	return(NULL);
}

void	start_threads(t_table *table)
{
	int i;

	i = 0;
	gettimeofday(&table->start_time, NULL);
	print_status(table->philo_array[0], "start time\n");
	while (i < table->philo_count)
	{
		if (pthread_create(&table->philo_array[i]->thread_id, NULL, philo_start,
				table->philo_array[i]) != 0)
		{
			free_both_arrays(table);
			error_exit(1, "thread creation failed\n");
		}
		i++;
	}
	pthread_create(&table->sup_thread_id, NULL, supervisor, table);
	for (i = 0; i < table->philo_count; i++)
    {
        pthread_join(table->philo_array[i]->thread_id, NULL);
    }
	pthread_join(table->sup_thread_id, NULL);
	print_status(table->philo_array[0], "end of simulatio\n");
}