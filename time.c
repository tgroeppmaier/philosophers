#include "philo.h"

/* takes the start time and returns the time
difference since start in ms */

long	get_time_diff(struct timeval start_time)
{
	struct timeval	current_time;
	long			time_diff;

	gettimeofday(&current_time, NULL);
	time_diff = (current_time.tv_sec - start_time.tv_sec) * 1000
		+ (current_time.tv_usec - start_time.tv_usec) / 1000;
	return (time_diff);
}

/* sleeps and checks every 500 us if it already slept long enough and if the
simulation should end */

bool	custom_usleep(t_table *table, useconds_t usec)
{
	long			elapsed_time;
	struct timeval	start_time;
	struct timeval	current_time;

	gettimeofday(&start_time, NULL);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		elapsed_time = (current_time.tv_sec - start_time.tv_sec) * 1e6
			+ (current_time.tv_usec - start_time.tv_usec);
		if (elapsed_time >= usec)
			break ;
		if (get_bool(&table->end_lock, &table->end_sim) == true)
			return (false);
		usleep(500);
	}
	return (true);
}
