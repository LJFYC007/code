i=0
while true; do
	./gen
	./clear
	./bf
    i=$(($i+1))
	if diff clear.out clear1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done