#include "philo.h"

void	init_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		printf("Failed to initialize mutex\n");
		exit(EXIT_FAILURE);
	}
}

void	lock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		printf("Failed to lock mutex\n");
		exit(EXIT_FAILURE);
	}
}

void	unlock_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		printf("Failed to unlock mutex\n");
		exit(EXIT_FAILURE);
	}
}

void	destroy_mutex(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
	{
		printf("Failed to destroy mutex\n");
		exit(EXIT_FAILURE);
	}
}

void	mutex_handle(pthread_mutex_t *mutex, int operation)
{
	if (operation == INIT)
		init_mutex(mutex);
	else if (operation == LOCK)
		lock_mutex(mutex);
	else if (operation == UNLOCK)
		unlock_mutex(mutex);
	else if (operation == DESTROY)
		destroy_mutex(mutex);
	else
	{
		printf("Invalid operation\n");
		exit(EXIT_FAILURE);
	}
}