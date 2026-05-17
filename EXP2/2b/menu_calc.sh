echo "Menu"
echo "1. Addition"
echo "2. Subtaction"
echo "3. Multiplication"
echo "4. Division"
echo "Enter your choice"
read ch
echo "Enter your first number:"
read a
echo "Enter your second number:"
read b
case $ch in
	1)
		echo "Sum=$((a+b))"
		;;
	2)
		echo "Difference=$((a-b))"
		;;
	3)
		echo "Multiplication=$((a*b))"
		;;
	4)
		echo "Divison=$((a/b))"
		;;
	*)
		echo "Invalid choice"
		;;
esac

