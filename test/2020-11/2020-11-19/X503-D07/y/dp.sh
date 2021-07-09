i=0
while true; do
	./gen
	./y
	./1
    i=$(($i+1))
	if diff y.out y1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
