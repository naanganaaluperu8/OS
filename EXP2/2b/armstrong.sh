echo "Enter a number:"
read n
temp=$n
sum=0
while [ $n -gt 0 ]
do
	digit=$((n%10))
	sum=$((sum+digit*digit*digit))
	n=$((n/10))
done
if [ $sum -eq $temp ]
then
	echo "The entered number is armstrong"
else
	echo "The entered number is not armstrong"
fi
