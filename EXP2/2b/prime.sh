echo "Enter the number:"
read n
i=2
echo "The prim numbers up to the limit $n are:"
while [ $i -le $n ]
do
	j=2
	flag=1
	while [ $j -lt $i ]
	do
		if [ $((i%j)) -eq 0 ]
		then
			flag=0
			break
		fi
		j=$((j+1))
	done
	if [ $flag -eq 1 ]
	then
		echo -n "$i  "
	fi
	i=$((i+1))
done
