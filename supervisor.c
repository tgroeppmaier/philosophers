#include "philo.h"

// long	get_time_diff_milliseconds(long past_time_milliseconds)
// {
// 	struct timeval	current_time;
// 	long			current_time_milliseconds;

// 	gettimeofday(&current_time, NULL);
// 	current_time_milliseconds = (current_time.tv_sec * 1e3)
// 		+ (current_time.tv_usec / 1e3);
// 	return (current_time_milliseconds - past_time_milliseconds);
// }

// long	get_time_diff(struct timeval start_time)
// {
// 	struct timeval	current_time;
// 	long			time_diff;

// 	gettimeofday(&current_time, NULL);
// 	time_diff = (current_time.tv_sec - start_time.tv_sec) * 1000
// 		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
// 	return (time_diff);
// }

void	*supervisor(void *data)
{
	int i;
	long last_meal;
	long time_diff;
	long current_time;
	t_table *table;

	table = (t_table *)data;
	i = 0;
	while (1)
	{
		i = 0;
		while (i < table->philo_count)
		{
			current_time = get_time_diff(table->start_time);
			last_meal = get_long(&table->philo_array[i]->lock,
					&table->philo_array[i]->last_meal_time);
			time_diff = current_time - last_meal;
			if (time_diff > table->time_to_die)
			{
				printf("timediff: %ld\n", time_diff);
				print_last_meal_time(table->philo_array[i]);
				// set_long(&table->end_lock, table->end_simulation, 1);
				exit(0);
			}
			i++;
		}
	}
}

// void	*supervisor(void *data)
// {
// 	int i;
// 	long last_meal;
// 	long time_diff;
// 	long current_time;
// 	t_table *table;

// 	table = (t_table *)data;
// 	i = 0;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < table->philo_count)
// 		{
// 			current_time = get_time_diff(table->start_time);
// 			last_meal = get_long(&table->philo_array[i]->lock,
// 					&table->philo_array[i]->last_meal_time);
// 			time_diff = current_time - last_meal;
// 			if (time_diff > table->time_to_die)
// 			{
// 				printf("timediff: %ld\n", time_diff);
// 				print_last_meal_time(table->philo_array[i]);
// 				// set_long(&table->end_lock, table->end_simulation, 1);
// 				exit(0);
// 			}
// 			i++;
// 		}
// 	}
// }