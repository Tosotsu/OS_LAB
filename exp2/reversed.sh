read -p "enter a number to be reversed" number
digit=number
reversed=0
while(($number>0))do
digit=$((number%10))
reversed=$((reversed*10+digit))
number=$((number/10))
done
echo "$reversed"


