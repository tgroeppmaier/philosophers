#!/bin/bash

your_command="./philo 5 600 200 200"
num_executions=1000
for ((i = 1; i <= num_executions; i++)); do
    eval "$your_command"
    sleep 0.5
done
