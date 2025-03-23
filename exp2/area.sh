#!/bin/bash

# Display options for shapes
echo "Select a shape to calculate its area:"
echo "1) Circle"
echo "2) Square"
echo "3) Rectangle"
echo "4) Triangle"
read -p "Enter your choice (1-4): " choice

# Calculate area based on user choice
case $choice in
    1)read -p "Enter radius of the circle: " radius
	area=$(echo "scale=2; 3.14 * $radius^2" | bc)
        ;;
    2)
        read -p "Enter side length of the square: " side
        area=$(echo "$side^2" | bc)
        ;;
    3)
        read -p "Enter length and width of rectangle (separated by space): " length width
        area=$(echo "$length * $width" | bc)
        ;;
    4)
        read -p "Enter base and height of triangle (separated by space): " base height
        area=$(echo "scale=2; 0.5 * $base * $height" | bc)
        ;;
    *)
        echo "Invalid choice! Please select a valid option."
        exit 1
        ;;
esac

# Output the calculated area
echo "The area is: $area"

