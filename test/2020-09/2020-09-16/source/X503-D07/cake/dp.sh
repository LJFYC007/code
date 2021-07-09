i=0
while true; do
	./gen
	./cake
	./bf
    i=$(($i+1))
	if diff cake.out cake1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
