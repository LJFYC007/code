i=0
while true; do
	./gen
	./junior
	./bf
    i=$(($i+1))
	if diff junior.out junior1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
