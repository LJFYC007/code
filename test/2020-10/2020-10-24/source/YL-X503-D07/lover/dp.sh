i=0
while true; do
	./gen
	./lover
	./bf
    i=$(($i+1))
	if diff lover.out lover1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
