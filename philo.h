#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_table
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_max_meals;
	long				start_time;
	bool				end_simulation;
	t_fork				*fork_array;
	t_philo				*philo_array;
}						t_table;

typedef struct s_philo
{
	int					id;
	int					meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				left_fork;
	t_fork				right_fork;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

bool					is_valid_int(char *str);
int						ft_atoi(const char *str);
#endif