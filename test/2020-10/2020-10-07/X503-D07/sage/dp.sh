i=0
while true; do
	./gen
	./sage
	./bf
    i=$(($i+1))
	if diff sage.out sage1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
