#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[31m"

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
	long				last_meal_time;
	bool				full;
	bool				alive;
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
	bool				even_philos;
	bool				end_sim;
	struct timeval		start_time;
	t_mtx				end_lock;
	t_mtx				print_mutex;
	pthread_t			sup_thread_id;
	t_fork				**fork_array;
	t_philo				**philo_array;
}						t_table;

/* check_input.c */
bool					check_input(int argc, char **argv);

/* initialize.c */
bool					initialize_data(t_table *table);

/* utils.c */
size_t					ft_strlen(const char *s);
int						ft_atoi(const char *str);
void					print_atomic(t_philo *philo, char *message);
void					print_last_meal_time(t_philo *philo);
void					print_status(t_philo *philo, char *status);

/* free.c */
bool					error_exit(bool ret, char *message);
void					free_forks(t_fork ***fork_array, int n,
							bool destroy_mutex);
void					free_philos(t_philo ***philo_array, int n,
							bool destroy_mutex);
void					free_table(t_table *table, bool destroy_mutex);
void					destroy_table_mtx(t_table *table);

/* start.c */
bool					start_threads(t_table *table);

/* getter_setter.c */
long					get_long(t_mtx *lock, long *value);
void					set_long(t_mtx *lock, long *old, long new);
bool					get_bool(t_mtx *lock, bool *value);
void					set_bool(t_mtx *lock, bool *old, bool new);

/* time. */
long					get_time_diff(struct timeval start_time);
bool					custom_usleep(t_table *table, useconds_t usec);

/* supervisor.c */
void					*supervisor(void *data);

/* operations.c */
bool					philo_eat_even(t_philo *philo);
bool					philo_eat_odd(t_philo *philo);
bool					philo_think(t_philo *philo);

#endif