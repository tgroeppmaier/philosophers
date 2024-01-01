#include "philo.h"

void	wait_until_time(struct timeval start_time, long wait_time)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	long time_diff = (current_time.tv_sec * 1e6 + current_time.tv_usec)
		- (start_time.tv_sec * 1e6 + start_time.tv_usec);
	if (time_diff < wait_time)
	{
		usleep(wait_time - time_diff);
	}
}

long	get_time_diff(struct timeval start_time)
{
	struct timeval	current_time;
	long			time_diff;

	gettimeofday(&current_time, NULL);
	time_diff = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	return (time_diff);
}

void	print_last_meal_time(t_philo *philo)
{
	long	time_diff;

	time_diff = get_time_diff(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld ms: %ld last meal time %ld\n\n", time_diff, philo->id, philo->last_meal_time);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

// int custom_usleep(t_table *table, useconds_t usec)
// {
// 	while(usec > 5000)
// 	{
// 		usleep(4930);
// 		if(get_bool(&table->end_lock, &table->end_simulation) == true)
// 			return(1);
// 		usec -= 5000;
// 	}
// 	usleep(usec);
// 	return(0);
// }

int custom_usleep(t_table *table, useconds_t usec)
{
	struct timeval start_time, current_time;
	long elapsed_time, sleep_time;

	gettimeofday(&start_time, NULL);

	while (usec > 0)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1e6 + (current_time.tv_usec - start_time.tv_usec);

		if (elapsed_time >= usec)
		{
			break;
		}

		if (get_bool(&table->end_lock, &table->end_simulation) == true)
		{
			return 1;
		}

		sleep_time = 5000 - (elapsed_time % 5000);
		usleep(sleep_time);

		usec -= sleep_time;
	}

	return 0;
}