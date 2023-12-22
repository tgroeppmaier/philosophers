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
	printf("%ld ms: %ld last meal time %ld\n", time_diff, philo->id, philo->last_meal_time);
	pthread_mutex_unlock(&philo->table->print_mutex);
}