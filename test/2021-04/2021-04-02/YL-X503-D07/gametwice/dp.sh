i=0
while true; do
	./gen
	./gametwice
	./bf
    i=$(($i+1))
	if diff gametwice.out gametwice1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
