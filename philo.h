#ifndef PHILO_H
# define PHILO_H

// #define BUFFER_SIZE 1000
# include <pthread.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	int					meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_count;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	struct timeval		start_time;
	bool				end_simulation;
	t_mtx				print_mutex;
	t_fork				**fork_array;
	t_philo				**philo_array;
}						t_table;

/* check_input.c */
void					check_input(int argc, char **argv);

/* initialize.c */
void					initialize_data(int argc, char **argv, t_table *table);

/* libft.c */
size_t					ft_strlen(const char *s);
int						ft_atoi(const char *str);

/* free.c */
void					error_exit(int exit_code, char *message);
void					free_array(void ***array, int n);
void					free_both_arrays(t_table *table);

/* start.c */
void	start_threads(t_table *table);
#endif