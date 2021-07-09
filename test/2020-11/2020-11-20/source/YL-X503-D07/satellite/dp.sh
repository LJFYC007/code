i=0
while true; do
	./gen
	./satellite
	./bf
    i=$(($i+1))
	if diff satellite.out satellite1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
