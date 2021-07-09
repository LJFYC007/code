i=0
while true; do
	./gen
	./std
	./snow
    i=$(($i+1))
	if diff snow.out snow1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
