i=0
while true; do
	./gen
	./B
	./bf
    i=$(($i+1))
	if diff output.txt ansput.txt ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
