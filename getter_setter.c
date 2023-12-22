#include "philo.h"

long get_long(t_mtx *lock, long *value)
{
	long ret;

	pthread_mutex_lock(lock);
	ret = *value;
	pthread_mutex_unlock(lock);
	return(ret);
}

void set_long(t_mtx *lock, long *old, long new)
{
	pthread_mutex_lock(lock);
	*old = new;
	pthread_mutex_unlock(lock);
}