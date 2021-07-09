i=0
while true; do
	./gen
	./ttds
	./bf
    i=$(($i+1))
	if diff ttds.out ttds1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
