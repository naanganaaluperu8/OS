echo "Enter the fisr number:"
read a
echo "Enter the second number:"
read b
echo "Enter the third number:"
read c
if [ $a -ge $b ] && [ $a -ge $c ]
then
	echo "Greatest number is $a"
elif [ $b -ge $c ] && [ $b -ge $a ]
then
	echo "Greatest number is $b"
else
	echo "Greatest number is $c"
fi
