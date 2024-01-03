#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long	time_diff;

	time_diff = get_time_diff(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld ms: %ld %s\n", time_diff, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

// void	print_status_nbr(t_philo *philo, char *status, long nbr)
// {
// 	long	time_diff;

// 	time_diff = get_time_diff(philo->table->start_time);
// 	pthread_mutex_lock(&philo->table->print_mutex);
// 	printf("%ld ms: %ld %s %ld\n", time_diff, philo->id, status, nbr);
// 	pthread_mutex_unlock(&philo->table->print_mutex);
// }

void	print_last_meal_time(t_philo *philo)
{
	long	time_diff;

	time_diff = get_time_diff(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld ms: %ld last meal time %ld\n\n", time_diff, philo->id,
		philo->last_meal_time);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	print_atomic(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->lock);
	if (philo->alive)
	{
		pthread_mutex_lock(&philo->table->end_lock);
		if (!philo->table->end_sim)
			print_status(philo, message);
		pthread_mutex_unlock(&philo->table->end_lock);
	}
	pthread_mutex_unlock(&philo->lock);
}