#include "philo.h"

bool error_exit(bool ret, char *message)
{
	write(2, message, ft_strlen(message));
	return(ret);
}

void	free_forks(t_fork ***fork_array, int n, bool destroy_mutex)
{
	int i;

	i = -1;
	while(++i < n)
	{
		// mutex_handle((*fork_array)[i]->fork, DESTROY);
		if(destroy_mutex)
			pthread_mutex_destroy(&(*fork_array)[i]->fork);
		free((*fork_array)[i]);
	}
	free(*fork_array);
	*fork_array = NULL;
}

void	free_philos(t_philo ***philo_array, int n, bool destroy_mutex)
{
	int i;

	i = -1;
	while(++i < n)
	{
		if(destroy_mutex)
			pthread_mutex_destroy(&(*philo_array)[i]->lock);
		free((*philo_array)[i]);
	}
	free(*philo_array);
	*philo_array = NULL;
}

void	free_table(t_table *table)
{
	free_forks(&table->fork_array, table->philo_count, true);
	free_philos(&table->philo_array, table->philo_count, true);
	pthread_mutex_destroy(&table->end_lock);
	pthread_mutex_destroy(&table->print_mutex);
}

// void	free_both_arrays(t_table *table)
// {
// }
