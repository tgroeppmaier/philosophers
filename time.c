#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

// Function that returns the current time since the 
// 1st of January 1970 in milliseconds
time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(void)
{
	time_t	start_time;
	time_t	end_time;
	time_t	time;

	start_time = get_time_in_ms();
	end_time = start_time + 2000;
	time = get_time_in_ms();
	printf("Time in ms = %ld. Time since start = %ld\n", time, time - start_time);
	while (get_time_in_ms() < end_time)
	{
		usleep(100 * 1000); // Suspend for 100 milliseconds
		time = get_time_in_ms();
		printf("Time in ms = %ld. Time since start = %ld\n",
						time, time - start_time);
	}
	return (0);
}