i=0
while true; do
	./gen
	./1
	./horsehunter
    i=$(($i+1))
	if diff horsehunter.out horsehunter1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
