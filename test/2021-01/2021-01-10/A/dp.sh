i=0
while true; do
	./gen
	./A
	./bf
    i=$(($i+1))
	if diff output.txt output1.txt ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
