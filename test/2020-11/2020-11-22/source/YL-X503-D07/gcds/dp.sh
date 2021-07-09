i=0
while true; do
	./gen
	./bf
	./gcds
    i=$(($i+1))
	if diff gcds.out gcds1.out;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
