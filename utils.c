#include "philo.h"

size_t	ft_strlen(const char *s)
{
	const char	*p;

	p = s;
	while (*p)
		++p;
	return (p - s);
}

int	ft_atoi(const char *str)
{
	int	c;
	int	sign;

	c = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		c = c * 10 + (*str - '0');
		str++;
	}
	return (c * sign);
}

void	print_status(t_philo *philo, char *status)
{
	long	time_diff;

	time_diff = get_time_diff(philo->table->start_time);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%ld ms: %ld %s\n", time_diff, philo->id, status);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

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