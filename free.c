#include "philo.h"

void	error_exit(int exit_code, char *message)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

void	free_array(t_philo ***array, int n)
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