i=0
while true; do
	./gen
	./u
	./bf
    i=$(($i+1))
	if diff u.out u1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
