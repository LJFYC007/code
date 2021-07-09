i=0
while true; do
	./gen
	./travel
	./bf
    i=$(($i+1))
	if diff travel.out travel1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
