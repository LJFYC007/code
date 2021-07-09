i=0
while true; do
	./gen
	./relics
	./bf
    i=$(($i+1))
	if diff relics.out relics1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
