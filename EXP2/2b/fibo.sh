echo "Enter a number:"
read n
a=0
b=1
i=1
echo "$a $b"
while [ $i -le $n ]
do
	c=$((a+b))
	a=$b
	b=$c
	echo " $c"
	i=$((i+1))
done
