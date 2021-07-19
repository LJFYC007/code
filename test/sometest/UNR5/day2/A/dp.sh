i=0
while true; do
	./gen
	./A
	./chk
    i=$(($i+1))
	if diff ansput.txt 111 ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
