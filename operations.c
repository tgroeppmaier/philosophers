#include "philo.h"

bool	check_end(t_table *table)
{
	if (get_bool(&table->end_lock, &table->end_sim) == true)
		return (true);
	return (false);
}

int unlock_forks(t_philo *philo, int ret)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	return(ret);
}

bool philo_think(t_philo *philo)
{
	long thinking_t;
	
	thinking_t = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if(thinking_t < 0)
		thinking_t = 0;
	if (check_end(philo->table))
		return(1);
	pthread_mutex_lock(&philo->table->end_lock);
	if(!philo->table->end_sim)
		print_status(philo, "is thinking\n");
	pthread_mutex_unlock(&philo->table->end_lock);
	if(philo->table->philo_count % 2 != 0)
		if(!custom_usleep(philo->table, thinking_t))
			return(false);
	return(true);
}

int	philo_eat_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (1);
	}
	print_status(philo, "has taken left fork\n");
	pthread_mutex_lock(&philo->right_fork->fork);
	if (check_end(philo->table))
		return(unlock_forks(philo, 1));
	set_long(&philo->lock, &philo->last_meal_time,
		get_time_diff(philo->table->start_time));
	print_status(philo, "has taken right fork\n");
	if (check_end(philo->table))
		return(unlock_forks(philo, 1));
	pthread_mutex_lock(&philo->lock);
	if(philo->alive)
		print_status(philo, "is eating\n");
	pthread_mutex_unlock(&philo->lock);
	if(!custom_usleep(philo->table, philo->table->time_to_eat))
		return(unlock_forks(philo, 1));
	return(unlock_forks(philo, 0));
}

int philo_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->right_fork->fork);
		return (1);
	}
	print_status(philo, "has taken right fork\n");
	pthread_mutex_lock(&philo->left_fork->fork);
	if (check_end(philo->table))
		return(unlock_forks(philo, 1));
	print_status(philo, "has taken left fork\n");
	set_long(&philo->lock, &philo->last_meal_time,
		get_time_diff(philo->table->start_time));
	if (check_end(philo->table))
		return(unlock_forks(philo, 1));
	pthread_mutex_lock(&philo->lock);
	if(philo->alive)
		print_status(philo, "is eating\n");
	pthread_mutex_unlock(&philo->lock);
	if(!custom_usleep(philo->table, philo->table->time_to_eat))
		return(unlock_forks(philo, 1));
	return(unlock_forks(philo, 0));
}
