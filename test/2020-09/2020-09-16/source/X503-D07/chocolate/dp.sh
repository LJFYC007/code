i=0
while true; do
	./gen
	./chocolate
	./bf
    i=$(($i+1))
	if diff chocolate.out chocolate1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
