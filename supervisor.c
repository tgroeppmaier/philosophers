#include "philo.h"

void	*supervisor(void *data)
{
	int i;
	int full_philos;
	long last_meal;
	long time_diff;
	long current_time;
	t_table *table;

	table = (t_table *)data;
	i = 0;
	while (get_long(&table->end_lock, &table->end_simulation) != 1)
	{
		i = 0;
		full_philos = 0;
		while (i < table->philo_count)
		{
			if(get_long(&table->philo_array[i]->lock, &table->philo_array[i]->full) == 1)
				full_philos++;
			current_time = get_time_diff(table->start_time);
			// printf("current time: %ld\n", current_time);
			last_meal = get_long(&table->philo_array[i]->lock,
					&table->philo_array[i]->last_meal_time);
			// printf("last_meal time: %ld\n", last_meal);
			time_diff = current_time - last_meal;
			// 	printf("timediff: %ld\n\n\n\n", time_diff);
			// printf("t2die: %ld\n", table->time_to_die);
			// time_diff = get_time_diff(table->start_time) - table->philo_array[i]->last_meal_time;
			if (time_diff > table->time_to_die)
			{
				// print_last_meal_time(table->philo_array[i]);
				pthread_mutex_lock(&table->print_mutex);
				printf(RED "%ld ms: philo %ld died!!!!\n" RESET, get_time_diff(table->start_time), table->philo_array[i]->id);
				pthread_mutex_unlock(&table->print_mutex);
				// printf("%ld ms: %ld %s\n", time_diff, philo->id, status);
				set_long(&table->end_lock, &table->end_simulation, 1);
				exit(1);
				break;
			}
			i++;
		}
		if(full_philos == table->philo_count)
		{
			// printf("full philos = %d\n", full_philos);
			break;
		}
		// if(get_long(&table->end_lock, &table->end_simulation) == 1)
		// 	break;
	}
	return(NULL);
}
