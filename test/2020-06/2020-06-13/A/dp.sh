i=0
while true; do
	./gen
	./A
	./bf
    i=$(($i+1))
	if diff A.out A1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
