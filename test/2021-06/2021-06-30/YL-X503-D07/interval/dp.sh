i=0
while true; do
	./gen
	./interval
	./bf
    i=$(($i+1))
	if diff interval.out interval1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
