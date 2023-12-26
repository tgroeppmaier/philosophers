#include "philo.h"

void	error_exit(int exit_code, char *message)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

void	free_array(void ***array, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		free((*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}

void	free_both_arrays(t_table *table)
{
	free_array((void ***)&table->philo_array, table->philo_count);
	free_array((void ***)&table->fork_array, table->philo_count);
}
