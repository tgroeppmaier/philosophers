#!/bin/bash

# Your command goes here
your_command="./philo 5 600 200 200"

# Number of times to execute the command
num_executions=1000

# Loop to execute the command
for ((i = 1; i <= num_executions; i++)); do
    # Execute the command
    eval "$your_command"

    # Sleep for half a second (0.5 seconds)
    sleep 0.5
done
