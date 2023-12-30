#Philosophers


- [Introduction](#introduction)
- [Ending Threads and freeing rescources](#ending-threads-and-freeing-rescources)
- [Monitor thread vs monitoring state by each Tread](#monitor-thread-vs-monitoring-state-by-each-tread)

### Introduction
This project is about implementing concurrency.

### Ending Threads and freeing rescources
Initialization of mutexes allocates Memory dynamically.
Therefore, if we dont need the mutex any more or, when the program ends, we need to free, in this case destroy it using the pthread_mutex_destroy function.
Destroying a locked mutex can result in undefined behaviour. We have to unlock it first.

### Monitor thread vs monitoring state by each Tread
