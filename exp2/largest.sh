echo "Enter three numbers: "
read a b c 

if (( $a > $b )); then
    if (( $a > $c )); then
        echo "The number $a is the greatest."
    else
        echo "The number $c is greater than $a."
    fi
elif (( $b > $c )); then
    echo "The number $b is the greatest."
else
    echo "The number $c is the greatest."
fi

