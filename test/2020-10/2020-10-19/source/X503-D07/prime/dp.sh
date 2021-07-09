i=0
while true; do
	./gen
	./prime
	./bf
    i=$(($i+1))
	if diff prime.out prime1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
