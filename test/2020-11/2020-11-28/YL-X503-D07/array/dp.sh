i=0
while true; do
	./gen
	./bf
	./dog
    i=$(($i+1))
	if diff array.out array1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
