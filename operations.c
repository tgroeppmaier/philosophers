#include "philo.h"

bool	check_end(t_table *table)
{
	if (get_long(&table->end_lock, &table->end_simulation) == 1)
		return (true);
	return (false);
}

int	philo_eat_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (1);
	}
	print_status(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->right_fork->fork);
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
		return (1);
	}
	set_long(&philo->lock, &philo->last_meal_time,
		get_time_diff(philo->table->start_time));
	print_status(philo, "has taken a fork\n");
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->right_fork->fork);
		return (1);
	}
	print_status(philo, "is eating\n");
	usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	return(0);
}

int philo_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->right_fork->fork);
		return (1);
	}
	print_status(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->left_fork->fork);
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (1);
	}
	set_long(&philo->lock, &philo->last_meal_time,
			 get_time_diff(philo->table->start_time));
	print_status(philo, "has taken a fork\n");
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->right_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (1);
	}
	print_status(philo, "is eating\n");
	usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
	return(0);
}