i=0
while true; do
	./gen
	./1
	./bf
    i=$(($i+1))
	if diff C.out C1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
