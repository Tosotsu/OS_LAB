#!/bin/bash

# Step 2: Read a number
echo "ENTER A NUMBER :"
read number

# Step 3: Initialize variables
original=$number
reversed=0

# Step 4: Use a while loop to reverse the number
while (($number > 0))do
    # Step 4.1.1: Get the last digit
    digit=$((number % 10))
    
    # Step 4.1.2: Append digit to reversed
    reversed=$((reversed * 10 + digit))
    
    # Step 4.1.3: Remove last digit from number
    number=$((number / 10))
done

# Step 5: Check if original is equal to reversed
if (($original==$reversed))then
    echo "$original is a palindrome."
else
    echo "$original is not a palindrome."
fi

# Step 6: Stop

