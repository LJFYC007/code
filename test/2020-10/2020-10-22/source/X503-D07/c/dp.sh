i=0
while true; do
	./gen
	./c
	./bf
    i=$(($i+1))
	if diff c.out c1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
