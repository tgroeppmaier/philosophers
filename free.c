#include "philo.h"

bool	error_exit(bool ret, char *message)
{
	write(2, message, ft_strlen(message));
	return (ret);
}

void	free_forks(t_fork ***fork_array, int n, bool destroy_mutex)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (destroy_mutex)
			pthread_mutex_destroy(&(*fork_array)[i]->fork);
		free((*fork_array)[i]);
	}
	free(*fork_array);
	*fork_array = NULL;
}

void	destroy_table_mtx(t_table *table)
{
	pthread_mutex_destroy(&table->end_lock);
	pthread_mutex_destroy(&table->print_mutex);
}

void	free_philos(t_philo ***philo_array, int n, bool destroy_mutex)
{
	int	i;

	i = -1;
	while (++i < n)
	{
		if (destroy_mutex)
			pthread_mutex_destroy(&(*philo_array)[i]->lock);
		free((*philo_array)[i]);
	}
	free(*philo_array);
	*philo_array = NULL;
}

void	free_table(t_table *table, bool destroy_mutex)
{
	free_forks(&table->fork_array, table->philo_count, destroy_mutex);
	free_philos(&table->philo_array, table->philo_count, destroy_mutex);
	if (destroy_mutex)
	{
		pthread_mutex_destroy(&table->end_lock);
		pthread_mutex_destroy(&table->print_mutex);
	}
}
