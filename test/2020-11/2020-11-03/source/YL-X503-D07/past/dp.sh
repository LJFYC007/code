i=0
while true; do
	./gen
	./past
	./bf
    i=$(($i+1))
	if diff past.out past1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
