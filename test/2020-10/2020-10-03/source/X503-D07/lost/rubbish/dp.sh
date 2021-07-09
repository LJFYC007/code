i=0
while true; do
	./gen
	./lost
	./bf
    i=$(($i+1))
	if diff lost.out lost1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
