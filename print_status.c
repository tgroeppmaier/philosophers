// In philo.h
typedef struct s_table
{
	// ...
	char buffer[BUFFER_SIZE];
	int buffer_index;
	pthread_mutex_t buffer_mutex;
	// ...
} t_table;

// In print_status.c
void append_to_buffer(t_table *table, char *str)
{
	pthread_mutex_lock(&table->buffer_mutex);
	while (*str && table->buffer_index < BUFFER_SIZE - 1) {
		table->buffer[table->buffer_index++] = *str++;
	}
	pthread_mutex_unlock(&table->buffer_mutex);
}

void append_number_to_buffer(t_table *table, long num)
{
	char num_str[20]; // Buffer to hold the string representation of the number
	int i = 0;

	// Convert the number to a string
	do {
		num_str[i++] = '0' + (num % 10);
		num /= 10;
	} while (num > 0);

	// Reverse the string and append it to the buffer
	pthread_mutex_lock(&table->buffer_mutex);
	while (--i >= 0 && table->buffer_index < BUFFER_SIZE - 1) {
		table->buffer[table->buffer_index++] = num_str[i];
	}
	pthread_mutex_unlock(&table->buffer_mutex);
}

void print_status(t_philo *philo, char *status)
{
	long time_diff = get_time_diff(philo->table->start_time);
	append_number_to_buffer(philo->table, time_diff);
	append_to_buffer(philo->table, " ms: ");
	append_number_to_buffer(philo->table, philo->id);
	append_to_buffer(philo->table, " ");
	append_to_buffer(philo->table, status);
	append_to_buffer(philo->table, "\n");
	pthread_mutex_lock(&philo->table->buffer_mutex);
	if (philo->table->buffer_index >= BUFFER_SIZE - 100) { // Leave some space for the next message
		write(1, philo->table->buffer, philo->table->buffer_index);
		philo->table->buffer_index = 0;
	}
	pthread_mutex_unlock(&philo->table->buffer_mutex);
}

// Don't forget to print the remaining messages at the end of your program
// This should be called from your main function or wherever your program ends
pthread_mutex_lock(&table->buffer_mutex);
if (table->buffer_index > 0) {
	write(1, table->buffer, table->buffer_index);
}
pthread_mutex_unlock(&table->buffer_mutex);