i=0
while true; do
	./gen
	./stone
	./std
    i=$(($i+1))
	if diff stone.out stone1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
