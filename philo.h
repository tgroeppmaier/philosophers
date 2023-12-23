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
	long				id;
	long				meals_counter;
	long				full;
	long				last_meal_time;
	t_mtx				lock;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					philo_count;
	long				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	struct timeval		start_time;
	long				end_simulation;
	t_mtx				end_lock;
	t_mtx				print_mutex;
	pthread_t			sup_thread_id;
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
void	print_status(t_philo *philo, char *status);

/* getter_setter.c */
long get_long(t_mtx *lock, long *value);
void set_long(t_mtx *lock, long *old, long new);

/* time. */

void	wait_until_time(struct timeval start_time, long wait_time);
long	get_time_diff(struct timeval start_time);
void	print_last_meal_time(t_philo *philo);

/* supervisor.c */
void	*supervisor(void *data);
#endif