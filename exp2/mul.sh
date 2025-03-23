echo "ENTER A NUMBER :"
read number
echo "MULTIPLICATION OF THE NUMBER :"
for((i=1; i<=10; i++))
do
product=$((number*i))
echo "$number * $i = $product"
done
