#include "philo.h"

bool	check_end(t_table *table)
{
	if (get_bool(&table->end_lock, &table->end_sim) == true)
		return (true);
	return (false);
}

bool	unlock_forks(t_philo *philo, bool ret)
{
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
	return (ret);
}

/* if philo count is odd && time 2 eat < time 2 sleep we need thinking period, to prevent philos
to snatch forks right after they wa thinking time = time to eat x 2 - time to sleep is implemented to make the system fair*/

bool	philo_think(t_philo *philo)
{
	long	thinking_t;

	thinking_t = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (thinking_t < 0)
		thinking_t = 0;
	if (check_end(philo->table))
		return (1);
	print_atomic(philo, "is thinking\n");
	if (philo->table->philo_count % 2 != 0)
		if (!custom_usleep(philo->table, thinking_t))
			return (false);
	return (true);
}

bool	philo_eat_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (1);
	}
	print_atomic(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->right_fork->fork);
	if (check_end(philo->table))
		return (unlock_forks(philo, false));
	set_long(&philo->lock, &philo->last_meal_time,
		get_time_diff(philo->table->start_time));
	print_atomic(philo, "has taken a fork\n");
	if (check_end(philo->table))
		return (unlock_forks(philo, false));
	print_atomic(philo, "is eating\n");
	if (!custom_usleep(philo->table, philo->table->time_to_eat))
		return (unlock_forks(philo, false));
	return (unlock_forks(philo, true));
}

bool	philo_eat_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	if (check_end(philo->table))
	{
		pthread_mutex_unlock(&philo->right_fork->fork);
		return (1);
	}
	print_atomic(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->left_fork->fork);
	if (check_end(philo->table))
		return (unlock_forks(philo, false));
	print_atomic(philo, "has taken  a fork\n");
	set_long(&philo->lock, &philo->last_meal_time,
		get_time_diff(philo->table->start_time));
	if (check_end(philo->table))
		return (unlock_forks(philo, false));
	print_atomic(philo, "is eating\n");
	if (!custom_usleep(philo->table, philo->table->time_to_eat))
		return (unlock_forks(philo, false));
	return (unlock_forks(philo, true));
}
