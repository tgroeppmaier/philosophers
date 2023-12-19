#include "philo.h"

void start_threads(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_count)
    {
        if (pthread_create(&table->philo_array[i]->thread_id, NULL, philosopher_routine, table->philo_array[i]) != 0)
		{
			free_both_arrays(table);
		}
            error_exit(1, "thread creation failed\n");
        i++;
    }
}