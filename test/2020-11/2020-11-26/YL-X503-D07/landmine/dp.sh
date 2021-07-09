i=0
while true; do
	./gen
	./landmine
	./hh
    i=$(($i+1))
	if diff landmine.out landmine1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
