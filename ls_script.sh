#!/bin/bash

while true
do
    ls | cat | wc -l | cat >> ls_output.txt
    sleep 1  # Sleep for 1 second before running ls again
done

