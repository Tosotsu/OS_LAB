#!/bin/bash

# Step 2: Read a number
echo "ENTER A NUMBER :"
read number

# Step 3: Initialize variables
sum=0

# Step 4: Use an until loop to calculate the sum of digits
until (($number == 0 )) do
    # Step 4.1.1: Get the last digit
    digit=$((number % 10))
    
    # Step 4.1.2: Add digit to sum
    sum=$((sum + digit))
    
    # Step 4.1.3: Remove last digit from number
    number=$((number / 10))
done

# Step 5: Output the sum
echo "The sum of the digits is: $sum"

# Step 6: Stop

