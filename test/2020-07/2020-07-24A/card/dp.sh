i=0
while true; do
	./gen
	./card
	./bf
    i=$(($i+1))
	if diff card.out card1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
