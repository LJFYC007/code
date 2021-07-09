i=0
while true; do
	./gen
	./count
	./bf
    i=$(($i+1))
	if diff count.out count1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
