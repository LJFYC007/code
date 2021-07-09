i=0
while true; do
	./gen
	./w
    ./1
    i=$(($i+1))
	if diff w.out w1.out  ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
